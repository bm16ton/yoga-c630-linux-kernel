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

MODULE_ALIAS("of:N*T*Crockchip,px30-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,px30-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-usb2phyC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-usb2phy");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-usb2phyC*");
