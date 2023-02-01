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

MODULE_ALIAS("usb:v106Cp3701d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp3702d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp3711d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp3712d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp3714d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp3715d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v16D8p5553d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v16D8p6512d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v1004p6000d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v0474p0754d*dc*dsc*dp*icFFiscFFip00in*");
MODULE_ALIAS("usb:v04E8p6640d*dc*dsc*dp*icFFisc00ip00in*");
MODULE_ALIAS("usb:v106Cp*d*dc*dsc*dp*icFFiscFDipFFin*");
MODULE_ALIAS("usb:v106Cp*d*dc*dsc*dp*icFFiscFEipFFin*");
MODULE_ALIAS("usb:v106Cp*d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v1FACp0151d*dc*dsc*dp*icFFiscFFipFFin*");
