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

MODULE_INFO(depends, "phy-generic,phy-sun4i-usb,musb_hdrc");

MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-musb");
MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-musbC*");
MODULE_ALIAS("of:N*T*Callwinner,sun6i-a31-musb");
MODULE_ALIAS("of:N*T*Callwinner,sun6i-a31-musbC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a33-musb");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a33-musbC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-musb");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-musbC*");
