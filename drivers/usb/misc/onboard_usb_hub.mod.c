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

MODULE_ALIAS("usb:v0424p2514d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp0411d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp5411d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp0414d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp5414d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0451p8140d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0451p8142d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("of:N*T*Cusb424,2514");
MODULE_ALIAS("of:N*T*Cusb424,2514C*");
MODULE_ALIAS("of:N*T*Cusb451,8140");
MODULE_ALIAS("of:N*T*Cusb451,8140C*");
MODULE_ALIAS("of:N*T*Cusb451,8142");
MODULE_ALIAS("of:N*T*Cusb451,8142C*");
MODULE_ALIAS("of:N*T*Cusbbda,411");
MODULE_ALIAS("of:N*T*Cusbbda,411C*");
MODULE_ALIAS("of:N*T*Cusbbda,5411");
MODULE_ALIAS("of:N*T*Cusbbda,5411C*");
MODULE_ALIAS("of:N*T*Cusbbda,414");
MODULE_ALIAS("of:N*T*Cusbbda,414C*");
MODULE_ALIAS("of:N*T*Cusbbda,5414");
MODULE_ALIAS("of:N*T*Cusbbda,5414C*");
