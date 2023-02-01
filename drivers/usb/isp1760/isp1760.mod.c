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

MODULE_INFO(depends, "udc-core");

MODULE_ALIAS("pci:v000010B5d00005406sv000010B5sd00009054bc06sc80i00*");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1760");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1760C*");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1761");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1761C*");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1763");
MODULE_ALIAS("of:N*T*Cnxp,usb-isp1763C*");
