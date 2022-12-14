/*
 * Device Tree Loader
 *
 * Copyright (C) 2013 Noralf Tronnes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/device.h>
#include <linux/firmware.h>
#include <linux/irqdomain.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_fdt.h>
#include <linux/of_platform.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>

#define MODNAME "fdt_loader"

static char *dtb;
module_param(dtb, charp, 0);
MODULE_PARM_DESC(dtb, "Device Tree Blob to load");

static char *remove_pdevs;
module_param(remove_pdevs, charp, 0);
MODULE_PARM_DESC(pdevs, "List of platform devices to remove");

static struct device fdt_loader_dev;


/*
 * Remove platform devices
 */

static void fdt_loader_remove_pdevs(void)
{
	struct device *dev;
	struct platform_device *pdev;
	char *devname;

	if (!remove_pdevs)
		return;

	while ((devname = strsep(&remove_pdevs, ","))) {
		dev = bus_find_device_by_name(&platform_bus_type, NULL, devname);
		if (!dev) {
			pr_warn(MODNAME ": remove_pdevs: could not find '%s'\n", devname);
			continue;
		}
		pdev = to_platform_device(dev);
		platform_device_unregister(pdev);
		pr_debug(MODNAME ": removed platform device '%s'\n", devname);
	}
}


/*
 *   Clock alias handling
 */

static int fdt_loader_clk_add_alias(const char *alias, const char *dev_id)
{
	struct clk *r = clk_get_sys(dev_id, NULL);
	struct clk_lookup *l;

	if (IS_ERR(r))
		return PTR_ERR(r);

	/* MAX_DEV_ID 20 is too small so we can't use clkdev_alloc() */
	l = kzalloc(GFP_KERNEL, sizeof(*l));
	if (!l) {
		clk_put(r);
		return -ENODEV;
	}
	l->clk = r;
	l->dev_id = alias;
	clk_put(r);
	clkdev_add(l);
	return 0;
}

static char *fdt_loader_make_name(struct device_node *np)
{
	const __be32 *reg;
	u64 addr;
	const __be32 *addrp;

	reg = of_get_property(np, "reg", NULL);
	if (!reg)
		return NULL;

	if (of_translate_address(np , reg)) {
		addr = of_translate_address(np, reg);
	} else {
		addrp = of_get_address(np, 0, NULL, NULL);
		if (addrp)
			addr = of_read_number(addrp, 1);
		else
			addr = OF_BAD_ADDR;
	}
	if (addr == OF_BAD_ADDR)
		return NULL;

	return kasprintf(GFP_KERNEL, "%llx.%s",
			(unsigned long long)addr, np->name);
}

static void fdt_loader_setup_clocks(void)
{
	struct device_node *np;
	char *dev_name;
	const char *clock_name;
	int rc;

	for_each_node_with_property(np, "named-clock") {
		if (of_property_read_string(np, "named-clock", &clock_name))
			continue;
		dev_name = fdt_loader_make_name(np);
		if (!dev_name) {
			pr_warn(MODNAME ": make_name() failed for '%s'\n", np->full_name);
			continue;
		}
		rc = fdt_loader_clk_add_alias(dev_name, clock_name);
		if (rc)
			pr_warn(MODNAME ": could not add clock alias '%s' for '%s' (%d)\n", dev_name, clock_name, rc);
		else
			pr_debug(MODNAME ": added clock alias '%s' => '%s'\n", dev_name, clock_name);
	}
};


/*
 *   IRQ Domain
*/

static int fdt_loader_irq_domain_xlate(struct irq_domain *d, struct device_node *ctrlr,
	const u32 *intspec, unsigned int intsize,
	unsigned long *out_hwirq, unsigned int *out_type)
{
	pr_debug("%s(intspec[0]=%d)\n", __func__, intspec[0]);
	*out_hwirq = intspec[0];
	return 0;
}

static struct irq_domain_ops fdt_loader_irq_domain_ops = {
	.xlate = fdt_loader_irq_domain_xlate
};

static void fdt_loader_setup_irq(void)
{
	struct device_node *np;
	struct irq_domain *domain;
	u32 first, size;

	np = of_find_compatible_node(NULL, NULL, "fdt_loader,irq_domain");
	if (!np)
		return;

	if (of_property_read_u32(np, "irq-domain-size", &size)) {
		pr_err(MODNAME ": %s: failed reading 'irq-domain-size'\n", of_node_full_name(np));
		return;
	}
	if (of_property_read_u32(np, "irq-domain-first", &first)) {
		pr_err(MODNAME ": %s: failed reading 'irq-domain-first'\n", of_node_full_name(np));
		return;
	}
	domain = irq_domain_add_legacy(np, size, first, first, &fdt_loader_irq_domain_ops, NULL);
	WARN_ON(!domain);
	of_node_put(np);
	pr_debug(MODNAME ": added legacy irq domain: size=%d, first_irq=%d, first_hwirq=%d\n", size, first, first);
}


/*
 *  /proc/device-tree2
 *
 *  Is there a way to get struct proc_dir_entry of /proc/device-tree ?
 */

#ifdef CONFIG_PROC_DEVICETREE
static struct proc_dir_entry *proc_device_tree;

static void proc_device_tree_reinit(void)
{
	struct device_node *root;

	proc_device_tree = proc_mkdir("device-tree2", NULL);
	if (proc_device_tree == NULL)
		return;
	root = of_find_node_by_path("/");
	if (root == NULL) {
		pr_debug(MODNAME ": /proc/device-tree: can't find root\n");
		return;
	}
	proc_device_tree_add_node(root, proc_device_tree);
	of_node_put(root);
}
#else
static void proc_device_tree_reinit(void) { }
#endif


/*
 *  Module
 */

static void *fdt_loader_kernel_tree_alloc(u64 size, u64 align)
{
        return kzalloc(size, GFP_KERNEL);
}

static void fdt_loader_fw_callback(const struct firmware *fw, void *context)
{
	int rc;

	if (!fw) {
		pr_err(MODNAME ": could not load firmware\n");
		return;
	}
	of_fdt_unflatten_tree((void *)fw->data, NULL, &of_root);
	fdt_loader_setup_irq();
	fdt_loader_setup_clocks();
        of_alias_scan(&fdt_loader_kernel_tree_alloc);
	rc = of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
	if (rc) {
		pr_err(MODNAME ": of_platform_populate() failed and returned %d\n", rc);
		return;
	}
	proc_device_tree_reinit();
	pr_info(MODNAME ": Device Tree loaded: %s\n", dtb);
}

void fdt_loader_release(struct device *dev)
{
}

static struct device fdt_loader_dev = {
	.init_name = MODNAME,
	.release = fdt_loader_release,
};

static __init int fdt_loader_init(void)
{
	int rc;

	fdt_loader_remove_pdevs();
	if (!dtb)
		return 0;

	rc = device_register(&fdt_loader_dev);
	if (rc) {
		put_device(&fdt_loader_dev);
		pr_err(MODNAME ": failed to register device");
		return rc;
	}
	request_firmware_nowait(THIS_MODULE, true, dtb, &fdt_loader_dev, GFP_KERNEL, NULL, fdt_loader_fw_callback);

	return 0;
}

/*
 * has to be called after arch_initcall where platform devices are registered,
   and before device_initcall (module_init) where drivers are probed
 */
rootfs_initcall(fdt_loader_init);

MODULE_DESCRIPTION("Device Tree Loader");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
