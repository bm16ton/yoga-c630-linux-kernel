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

MODULE_INFO(depends, "adis_lib,industrialio");

MODULE_ALIAS("of:N*T*Cadi,adis16470");
MODULE_ALIAS("of:N*T*Cadi,adis16470C*");
MODULE_ALIAS("of:N*T*Cadi,adis16475-1");
MODULE_ALIAS("of:N*T*Cadi,adis16475-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16475-2");
MODULE_ALIAS("of:N*T*Cadi,adis16475-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16475-3");
MODULE_ALIAS("of:N*T*Cadi,adis16475-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16477-1");
MODULE_ALIAS("of:N*T*Cadi,adis16477-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16477-2");
MODULE_ALIAS("of:N*T*Cadi,adis16477-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16477-3");
MODULE_ALIAS("of:N*T*Cadi,adis16477-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16465-1");
MODULE_ALIAS("of:N*T*Cadi,adis16465-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16465-2");
MODULE_ALIAS("of:N*T*Cadi,adis16465-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16465-3");
MODULE_ALIAS("of:N*T*Cadi,adis16465-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16467-1");
MODULE_ALIAS("of:N*T*Cadi,adis16467-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16467-2");
MODULE_ALIAS("of:N*T*Cadi,adis16467-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16467-3");
MODULE_ALIAS("of:N*T*Cadi,adis16467-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16500");
MODULE_ALIAS("of:N*T*Cadi,adis16500C*");
MODULE_ALIAS("of:N*T*Cadi,adis16505-1");
MODULE_ALIAS("of:N*T*Cadi,adis16505-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16505-2");
MODULE_ALIAS("of:N*T*Cadi,adis16505-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16505-3");
MODULE_ALIAS("of:N*T*Cadi,adis16505-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16507-1");
MODULE_ALIAS("of:N*T*Cadi,adis16507-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16507-2");
MODULE_ALIAS("of:N*T*Cadi,adis16507-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16507-3");
MODULE_ALIAS("of:N*T*Cadi,adis16507-3C*");
