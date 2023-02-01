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

MODULE_INFO(depends, "drm");

MODULE_ALIAS("of:N*T*Cboe,tv101wum-nl6");
MODULE_ALIAS("of:N*T*Cboe,tv101wum-nl6C*");
MODULE_ALIAS("of:N*T*Cauo,kd101n80-45na");
MODULE_ALIAS("of:N*T*Cauo,kd101n80-45naC*");
MODULE_ALIAS("of:N*T*Cboe,tv101wum-n53");
MODULE_ALIAS("of:N*T*Cboe,tv101wum-n53C*");
MODULE_ALIAS("of:N*T*Cauo,b101uan08.3");
MODULE_ALIAS("of:N*T*Cauo,b101uan08.3C*");
MODULE_ALIAS("of:N*T*Cboe,tv105wum-nw0");
MODULE_ALIAS("of:N*T*Cboe,tv105wum-nw0C*");
MODULE_ALIAS("of:N*T*Cboe,tv110c9m-ll3");
MODULE_ALIAS("of:N*T*Cboe,tv110c9m-ll3C*");
MODULE_ALIAS("of:N*T*Cinnolux,hj110iz-01a");
MODULE_ALIAS("of:N*T*Cinnolux,hj110iz-01aC*");
