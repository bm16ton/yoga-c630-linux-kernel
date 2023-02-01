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

MODULE_ALIAS("of:N*T*Cti,741g125");
MODULE_ALIAS("of:N*T*Cti,741g125C*");
MODULE_ALIAS("of:N*T*Cti,742g125");
MODULE_ALIAS("of:N*T*Cti,742g125C*");
MODULE_ALIAS("of:N*T*Cti,74125");
MODULE_ALIAS("of:N*T*Cti,74125C*");
MODULE_ALIAS("of:N*T*Cti,74365");
MODULE_ALIAS("of:N*T*Cti,74365C*");
MODULE_ALIAS("of:N*T*Cti,74244");
MODULE_ALIAS("of:N*T*Cti,74244C*");
MODULE_ALIAS("of:N*T*Cti,741624");
MODULE_ALIAS("of:N*T*Cti,741624C*");
MODULE_ALIAS("of:N*T*Cti,741g74");
MODULE_ALIAS("of:N*T*Cti,741g74C*");
MODULE_ALIAS("of:N*T*Cti,7474");
MODULE_ALIAS("of:N*T*Cti,7474C*");
MODULE_ALIAS("of:N*T*Cti,74175");
MODULE_ALIAS("of:N*T*Cti,74175C*");
MODULE_ALIAS("of:N*T*Cti,74174");
MODULE_ALIAS("of:N*T*Cti,74174C*");
MODULE_ALIAS("of:N*T*Cti,74273");
MODULE_ALIAS("of:N*T*Cti,74273C*");
MODULE_ALIAS("of:N*T*Cti,7416374");
MODULE_ALIAS("of:N*T*Cti,7416374C*");
