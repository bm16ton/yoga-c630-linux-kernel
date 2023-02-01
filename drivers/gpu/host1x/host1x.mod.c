#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cnvidia,tegra234-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra234-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra194-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra194-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra186-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra186-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra124-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra124-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra114-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra114-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra30-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra30-host1xC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-host1x");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-host1xC*");
