// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2020 Birger Koblitz <mail@birger-koblitz.de>
 * Copyright (C) 2020 Bert Vermeulen <bert@biot.com>
 * Copyright (C) 2020 John Crispin <john@phrozen.org>
 */

#include <linux/of_irq.h>
#include <linux/irqchip.h>
#include <linux/spinlock.h>
#include <linux/of_address.h>
#include <linux/irqchip/chained_irq.h>

/* Global Interrupt Mask Register */
#define RTL_ICTL_GIMR		0x00
/* Global Interrupt Status Register */
#define RTL_ICTL_GISR		0x04
/* Interrupt Routing Registers */
#define RTL_ICTL_IRR0		0x08
#define RTL_ICTL_IRR1		0x0c
#define RTL_ICTL_IRR2		0x10
#define RTL_ICTL_IRR3		0x14

#define RTL_ICTL_NUM_INPUTS	32

#define REG(x)		(realtek_ictl_base + x)

static DEFINE_RAW_SPINLOCK(irq_lock);
static void __iomem *realtek_ictl_base;

/*
 * IRR0-IRR3 store 4 bits per interrupt, but Realtek uses inverted numbering,
 * placing IRQ 31 in the first four bits. A routing value of '0' means the
 * interrupt is left disconnected. Routing values {1..15} connect to output
 * lines {0..14}.
 */
#define IRR_OFFSET(idx)		(4 * (3 - (idx * 4) / 32))
#define IRR_SHIFT(idx)		((idx * 4) % 32)

static void write_irr(void __iomem *irr0, int idx, u32 value)
{
	unsigned int offset = IRR_OFFSET(idx);
	unsigned int shift = IRR_SHIFT(idx);
	u32 irr;

	irr = readl(irr0 + offset) & ~(0xf << shift);
	irr |= (value & 0xf) << shift;
	writel(irr, irr0 + offset);
}

static void realtek_ictl_unmask_irq(struct irq_data *i)
{
	unsigned long flags;
	u32 value;

	raw_spin_lock_irqsave(&irq_lock, flags);

	value = readl(REG(RTL_ICTL_GIMR));
	value |= BIT(i->hwirq);
	writel(value, REG(RTL_ICTL_GIMR));

	raw_spin_unlock_irqrestore(&irq_lock, flags);
}

static void realtek_ictl_mask_irq(struct irq_data *i)
{
	unsigned long flags;
	u32 value;

	raw_spin_lock_irqsave(&irq_lock, flags);

	value = readl(REG(RTL_ICTL_GIMR));
	value &= ~BIT(i->hwirq);
	writel(value, REG(RTL_ICTL_GIMR));

	raw_spin_unlock_irqrestore(&irq_lock, flags);
}

static struct irq_chip realtek_ictl_irq = {
	.name = "realtek-rtl-intc",
	.irq_mask = realtek_ictl_mask_irq,
	.irq_unmask = realtek_ictl_unmask_irq,
};

static int intc_map(struct irq_domain *d, unsigned int irq, irq_hw_number_t hw)
{
<<<<<<< HEAD
	unsigned long flags;

	irq_set_chip_and_handler(irq, &realtek_ictl_irq, handle_level_irq);

	raw_spin_lock_irqsave(&irq_lock, flags);
	write_irr(REG(RTL_ICTL_IRR0), hw, 1);
	raw_spin_unlock_irqrestore(&irq_lock, flags);
=======
	irq_set_chip_and_handler(irq, &realtek_ictl_irq, handle_level_irq);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	return 0;
}

static const struct irq_domain_ops irq_domain_ops = {
	.map = intc_map,
	.xlate = irq_domain_xlate_onecell,
};

static void realtek_irq_dispatch(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct irq_domain *domain;
	unsigned long pending;
	unsigned int soc_int;

	chained_irq_enter(chip, desc);
	pending = readl(REG(RTL_ICTL_GIMR)) & readl(REG(RTL_ICTL_GISR));

	if (unlikely(!pending)) {
		spurious_interrupt();
		goto out;
	}

	domain = irq_desc_get_handler_data(desc);
	for_each_set_bit(soc_int, &pending, 32)
		generic_handle_domain_irq(domain, soc_int);

out:
	chained_irq_exit(chip, desc);
}

<<<<<<< HEAD
=======
/*
 * SoC interrupts are cascaded to MIPS CPU interrupts according to the
 * interrupt-map in the device tree. Each SoC interrupt gets 4 bits for
 * the CPU interrupt in an Interrupt Routing Register. Max 32 SoC interrupts
 * thus go into 4 IRRs. A routing value of '0' means the interrupt is left
 * disconnected. Routing values {1..15} connect to output lines {0..14}.
 */
static int __init map_interrupts(struct device_node *node, struct irq_domain *domain)
{
	struct device_node *cpu_ictl;
	const __be32 *imap;
	u32 imaplen, soc_int, cpu_int, tmp, regs[4];
	int ret, i, irr_regs[] = {
		RTL_ICTL_IRR3,
		RTL_ICTL_IRR2,
		RTL_ICTL_IRR1,
		RTL_ICTL_IRR0,
	};
	u8 mips_irqs_set;

	ret = of_property_read_u32(node, "#address-cells", &tmp);
	if (ret || tmp)
		return -EINVAL;

	imap = of_get_property(node, "interrupt-map", &imaplen);
	if (!imap || imaplen % 3)
		return -EINVAL;

	mips_irqs_set = 0;
	memset(regs, 0, sizeof(regs));
	for (i = 0; i < imaplen; i += 3 * sizeof(u32)) {
		soc_int = be32_to_cpup(imap);
		if (soc_int > 31)
			return -EINVAL;

		cpu_ictl = of_find_node_by_phandle(be32_to_cpup(imap + 1));
		if (!cpu_ictl)
			return -EINVAL;
		ret = of_property_read_u32(cpu_ictl, "#interrupt-cells", &tmp);
		of_node_put(cpu_ictl);
		if (ret || tmp != 1)
			return -EINVAL;

		cpu_int = be32_to_cpup(imap + 2);
		if (cpu_int > 7 || cpu_int < 2)
			return -EINVAL;

		if (!(mips_irqs_set & BIT(cpu_int))) {
			irq_set_chained_handler_and_data(cpu_int, realtek_irq_dispatch,
							 domain);
			mips_irqs_set |= BIT(cpu_int);
		}

		/* Use routing values (1..6) for CPU interrupts (2..7) */
		regs[(soc_int * 4) / 32] |= (cpu_int - 1) << (soc_int * 4) % 32;
		imap += 3;
	}

	for (i = 0; i < 4; i++)
		writel(regs[i], REG(irr_regs[i]));

	return 0;
}

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
static int __init realtek_rtl_of_init(struct device_node *node, struct device_node *parent)
{
	struct of_phandle_args oirq;
	struct irq_domain *domain;
	unsigned int soc_irq;
	int parent_irq;

	realtek_ictl_base = of_iomap(node, 0);
	if (!realtek_ictl_base)
		return -ENXIO;

	/* Disable all cascaded interrupts and clear routing */
	writel(0, REG(RTL_ICTL_GIMR));
	for (soc_irq = 0; soc_irq < RTL_ICTL_NUM_INPUTS; soc_irq++)
		write_irr(REG(RTL_ICTL_IRR0), soc_irq, 0);

	if (WARN_ON(!of_irq_count(node))) {
		/*
		 * If DT contains no parent interrupts, assume MIPS CPU IRQ 2
		 * (HW0) is connected to the first output. This is the case for
		 * all known hardware anyway. "interrupt-map" is deprecated, so
		 * don't bother trying to parse that.
		 */
		oirq.np = of_find_compatible_node(NULL, NULL, "mti,cpu-interrupt-controller");
		oirq.args_count = 1;
		oirq.args[0] = 2;

		parent_irq = irq_create_of_mapping(&oirq);

		of_node_put(oirq.np);
	} else {
		parent_irq = of_irq_get(node, 0);
	}

	if (parent_irq < 0)
		return parent_irq;
	else if (!parent_irq)
		return -ENODEV;

	domain = irq_domain_add_linear(node, RTL_ICTL_NUM_INPUTS, &irq_domain_ops, NULL);
	if (!domain)
		return -ENOMEM;

	irq_set_chained_handler_and_data(parent_irq, realtek_irq_dispatch, domain);

	return 0;
}

IRQCHIP_DECLARE(realtek_rtl_intc, "realtek,rtl-intc", realtek_rtl_of_init);
