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

MODULE_INFO(depends, "libphy,mdio-xgene,of_mdio");

MODULE_ALIAS("of:N*T*Capm,xgene-enet");
MODULE_ALIAS("of:N*T*Capm,xgene-enetC*");
MODULE_ALIAS("of:N*T*Capm,xgene1-sgenet");
MODULE_ALIAS("of:N*T*Capm,xgene1-sgenetC*");
MODULE_ALIAS("of:N*T*Capm,xgene1-xgenet");
MODULE_ALIAS("of:N*T*Capm,xgene1-xgenetC*");
MODULE_ALIAS("of:N*T*Capm,xgene2-sgenet");
MODULE_ALIAS("of:N*T*Capm,xgene2-sgenetC*");
MODULE_ALIAS("of:N*T*Capm,xgene2-xgenet");
MODULE_ALIAS("of:N*T*Capm,xgene2-xgenetC*");
MODULE_ALIAS("acpi*:APMC0D05:*");
MODULE_ALIAS("acpi*:APMC0D30:*");
MODULE_ALIAS("acpi*:APMC0D31:*");
MODULE_ALIAS("acpi*:APMC0D3F:*");
MODULE_ALIAS("acpi*:APMC0D26:*");
MODULE_ALIAS("acpi*:APMC0D25:*");
