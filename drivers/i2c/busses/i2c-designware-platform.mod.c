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

MODULE_INFO(depends, "i2c-designware-core");

MODULE_ALIAS("acpi*:INT33C2:*");
MODULE_ALIAS("acpi*:INT33C3:*");
MODULE_ALIAS("acpi*:INT3432:*");
MODULE_ALIAS("acpi*:INT3433:*");
MODULE_ALIAS("acpi*:80860F41:*");
MODULE_ALIAS("acpi*:808622C1:*");
MODULE_ALIAS("acpi*:AMD0010:*");
MODULE_ALIAS("acpi*:AMDI0010:*");
MODULE_ALIAS("acpi*:AMDI0019:*");
MODULE_ALIAS("acpi*:AMDI0510:*");
MODULE_ALIAS("acpi*:APMC0D0F:*");
MODULE_ALIAS("acpi*:HISI02A1:*");
MODULE_ALIAS("acpi*:HISI02A2:*");
MODULE_ALIAS("acpi*:HISI02A3:*");
MODULE_ALIAS("acpi*:HYGO0010:*");
MODULE_ALIAS("of:N*T*Csnps,designware-i2c");
MODULE_ALIAS("of:N*T*Csnps,designware-i2cC*");
MODULE_ALIAS("of:N*T*Cmscc,ocelot-i2c");
MODULE_ALIAS("of:N*T*Cmscc,ocelot-i2cC*");
MODULE_ALIAS("of:N*T*Cbaikal,bt1-sys-i2c");
MODULE_ALIAS("of:N*T*Cbaikal,bt1-sys-i2cC*");
