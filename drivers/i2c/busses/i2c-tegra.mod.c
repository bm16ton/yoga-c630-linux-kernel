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

MODULE_ALIAS("acpi*:NVDA0101:*");
MODULE_ALIAS("acpi*:NVDA0201:*");
MODULE_ALIAS("acpi*:NVDA0301:*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra194-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra194-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra186-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra186-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-i2c-vi");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-i2c-viC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra210-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra124-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra124-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra114-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra114-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra30-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra30-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-i2c");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-i2cC*");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-i2c-dvc");
MODULE_ALIAS("of:N*T*Cnvidia,tegra20-i2c-dvcC*");
