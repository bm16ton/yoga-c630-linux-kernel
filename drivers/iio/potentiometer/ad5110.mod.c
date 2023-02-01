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

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("i2c:ad5110-10");
MODULE_ALIAS("i2c:ad5110-80");
MODULE_ALIAS("i2c:ad5112-05");
MODULE_ALIAS("i2c:ad5112-10");
MODULE_ALIAS("i2c:ad5112-80");
MODULE_ALIAS("i2c:ad5114-10");
MODULE_ALIAS("i2c:ad5114-80");
MODULE_ALIAS("of:N*T*Cadi,ad5110-10");
MODULE_ALIAS("of:N*T*Cadi,ad5110-10C*");
MODULE_ALIAS("of:N*T*Cadi,ad5110-80");
MODULE_ALIAS("of:N*T*Cadi,ad5110-80C*");
MODULE_ALIAS("of:N*T*Cadi,ad5112-05");
MODULE_ALIAS("of:N*T*Cadi,ad5112-05C*");
MODULE_ALIAS("of:N*T*Cadi,ad5112-10");
MODULE_ALIAS("of:N*T*Cadi,ad5112-10C*");
MODULE_ALIAS("of:N*T*Cadi,ad5112-80");
MODULE_ALIAS("of:N*T*Cadi,ad5112-80C*");
MODULE_ALIAS("of:N*T*Cadi,ad5114-10");
MODULE_ALIAS("of:N*T*Cadi,ad5114-10C*");
MODULE_ALIAS("of:N*T*Cadi,ad5114-80");
MODULE_ALIAS("of:N*T*Cadi,ad5114-80C*");
