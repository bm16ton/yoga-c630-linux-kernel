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

MODULE_ALIAS("i2c:fan53526");
MODULE_ALIAS("i2c:fan53555");
MODULE_ALIAS("i2c:syr827");
MODULE_ALIAS("i2c:syr828");
MODULE_ALIAS("i2c:tcs4525");
MODULE_ALIAS("i2c:tcs4526");
MODULE_ALIAS("of:N*T*Cfcs,fan53526");
MODULE_ALIAS("of:N*T*Cfcs,fan53526C*");
MODULE_ALIAS("of:N*T*Cfcs,fan53555");
MODULE_ALIAS("of:N*T*Cfcs,fan53555C*");
MODULE_ALIAS("of:N*T*Csilergy,syr827");
MODULE_ALIAS("of:N*T*Csilergy,syr827C*");
MODULE_ALIAS("of:N*T*Csilergy,syr828");
MODULE_ALIAS("of:N*T*Csilergy,syr828C*");
MODULE_ALIAS("of:N*T*Ctcs,tcs4525");
MODULE_ALIAS("of:N*T*Ctcs,tcs4525C*");
MODULE_ALIAS("of:N*T*Ctcs,tcs4526");
MODULE_ALIAS("of:N*T*Ctcs,tcs4526C*");
