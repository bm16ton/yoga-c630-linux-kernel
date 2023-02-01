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

MODULE_INFO(depends, "usbnet,mii");

MODULE_ALIAS("usb:v0B95p1790d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v0B95p178Ad*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v04B4p3610d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v2001p4A00d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v0DF6p0072d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v04E8pA100d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v17EFp304Bd*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v050Dp0128d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v0930p0A13d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v0711p0179d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v07C9p000Ed*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v07C9p000Fd*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v07C9p0010d*dc*dsc*dp*icFFiscFFip00in*");
