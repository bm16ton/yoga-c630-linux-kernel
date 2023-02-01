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

MODULE_ALIAS("platform:ehci-platform");
MODULE_ALIAS("acpi*:PNP0D20:*");
MODULE_ALIAS("of:N*T*Cvia,vt8500-ehci");
MODULE_ALIAS("of:N*T*Cvia,vt8500-ehciC*");
MODULE_ALIAS("of:N*T*Cwm,prizm-ehci");
MODULE_ALIAS("of:N*T*Cwm,prizm-ehciC*");
MODULE_ALIAS("of:N*T*Cgeneric-ehci");
MODULE_ALIAS("of:N*T*Cgeneric-ehciC*");
MODULE_ALIAS("of:N*T*Ccavium,octeon-6335-ehci");
MODULE_ALIAS("of:N*T*Ccavium,octeon-6335-ehciC*");
