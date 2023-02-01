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

MODULE_INFO(depends, "libphy,phylink,of_mdio");

MODULE_ALIAS("of:N*T*Ccdns,at91sam9260-macb");
MODULE_ALIAS("of:N*T*Ccdns,at91sam9260-macbC*");
MODULE_ALIAS("of:N*T*Ccdns,macb");
MODULE_ALIAS("of:N*T*Ccdns,macbC*");
MODULE_ALIAS("of:N*T*Ccdns,np4-macb");
MODULE_ALIAS("of:N*T*Ccdns,np4-macbC*");
MODULE_ALIAS("of:N*T*Ccdns,pc302-gem");
MODULE_ALIAS("of:N*T*Ccdns,pc302-gemC*");
MODULE_ALIAS("of:N*T*Ccdns,gem");
MODULE_ALIAS("of:N*T*Ccdns,gemC*");
MODULE_ALIAS("of:N*T*Ccdns,sam9x60-macb");
MODULE_ALIAS("of:N*T*Ccdns,sam9x60-macbC*");
MODULE_ALIAS("of:N*T*Catmel,sama5d2-gem");
MODULE_ALIAS("of:N*T*Catmel,sama5d2-gemC*");
MODULE_ALIAS("of:N*T*Catmel,sama5d29-gem");
MODULE_ALIAS("of:N*T*Catmel,sama5d29-gemC*");
MODULE_ALIAS("of:N*T*Catmel,sama5d3-gem");
MODULE_ALIAS("of:N*T*Catmel,sama5d3-gemC*");
MODULE_ALIAS("of:N*T*Catmel,sama5d3-macb");
MODULE_ALIAS("of:N*T*Catmel,sama5d3-macbC*");
MODULE_ALIAS("of:N*T*Catmel,sama5d4-gem");
MODULE_ALIAS("of:N*T*Catmel,sama5d4-gemC*");
MODULE_ALIAS("of:N*T*Ccdns,at91rm9200-emac");
MODULE_ALIAS("of:N*T*Ccdns,at91rm9200-emacC*");
MODULE_ALIAS("of:N*T*Ccdns,emac");
MODULE_ALIAS("of:N*T*Ccdns,emacC*");
MODULE_ALIAS("of:N*T*Ccdns,zynqmp-gem");
MODULE_ALIAS("of:N*T*Ccdns,zynqmp-gemC*");
MODULE_ALIAS("of:N*T*Ccdns,zynq-gem");
MODULE_ALIAS("of:N*T*Ccdns,zynq-gemC*");
MODULE_ALIAS("of:N*T*Csifive,fu540-c000-gem");
MODULE_ALIAS("of:N*T*Csifive,fu540-c000-gemC*");
MODULE_ALIAS("of:N*T*Cmicrochip,mpfs-macb");
MODULE_ALIAS("of:N*T*Cmicrochip,mpfs-macbC*");
MODULE_ALIAS("of:N*T*Cmicrochip,sama7g5-gem");
MODULE_ALIAS("of:N*T*Cmicrochip,sama7g5-gemC*");
MODULE_ALIAS("of:N*T*Cmicrochip,sama7g5-emac");
MODULE_ALIAS("of:N*T*Cmicrochip,sama7g5-emacC*");
MODULE_ALIAS("of:N*T*Cxlnx,zynqmp-gem");
MODULE_ALIAS("of:N*T*Cxlnx,zynqmp-gemC*");
MODULE_ALIAS("of:N*T*Cxlnx,zynq-gem");
MODULE_ALIAS("of:N*T*Cxlnx,zynq-gemC*");
MODULE_ALIAS("of:N*T*Cxlnx,versal-gem");
MODULE_ALIAS("of:N*T*Cxlnx,versal-gemC*");
