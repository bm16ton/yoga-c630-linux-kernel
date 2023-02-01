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

MODULE_INFO(depends, "mac80211,cfg80211");

MODULE_ALIAS("usb:v16C1p1CDEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2EF5p0008d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2EF5p000Ad*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "9BEF33716C641AEF11FFB53");
