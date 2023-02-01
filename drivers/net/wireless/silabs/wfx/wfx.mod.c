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

MODULE_ALIAS("of:N*T*Csilabs,wf200");
MODULE_ALIAS("of:N*T*Csilabs,wf200C*");
MODULE_ALIAS("of:N*T*Csilabs,brd4001a");
MODULE_ALIAS("of:N*T*Csilabs,brd4001aC*");
MODULE_ALIAS("of:N*T*Csilabs,brd8022a");
MODULE_ALIAS("of:N*T*Csilabs,brd8022aC*");
MODULE_ALIAS("of:N*T*Csilabs,brd8023a");
MODULE_ALIAS("of:N*T*Csilabs,brd8023aC*");
MODULE_ALIAS("sdio:c*v0000d1000*");
MODULE_ALIAS("of:N*T*Csilabs,wf200");
MODULE_ALIAS("of:N*T*Csilabs,wf200C*");
MODULE_ALIAS("of:N*T*Csilabs,brd4001a");
MODULE_ALIAS("of:N*T*Csilabs,brd4001aC*");
MODULE_ALIAS("of:N*T*Csilabs,brd8022a");
MODULE_ALIAS("of:N*T*Csilabs,brd8022aC*");
MODULE_ALIAS("of:N*T*Csilabs,brd8023a");
MODULE_ALIAS("of:N*T*Csilabs,brd8023aC*");
MODULE_ALIAS("spi:wf200");
MODULE_ALIAS("spi:brd4001a");
MODULE_ALIAS("spi:brd8022a");
MODULE_ALIAS("spi:brd8023a");
