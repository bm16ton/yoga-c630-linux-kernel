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

MODULE_INFO(depends, "libahci_platform,libata,libahci");

MODULE_ALIAS("of:N*T*Capm,xgene-ahci");
MODULE_ALIAS("of:N*T*Capm,xgene-ahciC*");
MODULE_ALIAS("of:N*T*Capm,xgene-ahci-v2");
MODULE_ALIAS("of:N*T*Capm,xgene-ahci-v2C*");
MODULE_ALIAS("acpi*:APMC0D0D:*");
MODULE_ALIAS("acpi*:APMC0D32:*");

MODULE_INFO(srcversion, "A0E13C259BA71C6DD9D2741");
