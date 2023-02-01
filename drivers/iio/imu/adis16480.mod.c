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

MODULE_ALIAS("of:N*T*Cadi,adis16375");
MODULE_ALIAS("of:N*T*Cadi,adis16375C*");
MODULE_ALIAS("of:N*T*Cadi,adis16480");
MODULE_ALIAS("of:N*T*Cadi,adis16480C*");
MODULE_ALIAS("of:N*T*Cadi,adis16485");
MODULE_ALIAS("of:N*T*Cadi,adis16485C*");
MODULE_ALIAS("of:N*T*Cadi,adis16488");
MODULE_ALIAS("of:N*T*Cadi,adis16488C*");
MODULE_ALIAS("of:N*T*Cadi,adis16490");
MODULE_ALIAS("of:N*T*Cadi,adis16490C*");
MODULE_ALIAS("of:N*T*Cadi,adis16495-1");
MODULE_ALIAS("of:N*T*Cadi,adis16495-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16495-2");
MODULE_ALIAS("of:N*T*Cadi,adis16495-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16495-3");
MODULE_ALIAS("of:N*T*Cadi,adis16495-3C*");
MODULE_ALIAS("of:N*T*Cadi,adis16497-1");
MODULE_ALIAS("of:N*T*Cadi,adis16497-1C*");
MODULE_ALIAS("of:N*T*Cadi,adis16497-2");
MODULE_ALIAS("of:N*T*Cadi,adis16497-2C*");
MODULE_ALIAS("of:N*T*Cadi,adis16497-3");
MODULE_ALIAS("of:N*T*Cadi,adis16497-3C*");
MODULE_ALIAS("spi:adis16375");
MODULE_ALIAS("spi:adis16480");
MODULE_ALIAS("spi:adis16485");
MODULE_ALIAS("spi:adis16488");
MODULE_ALIAS("spi:adis16490");
MODULE_ALIAS("spi:adis16495-1");
MODULE_ALIAS("spi:adis16495-2");
MODULE_ALIAS("spi:adis16495-3");
MODULE_ALIAS("spi:adis16497-1");
MODULE_ALIAS("spi:adis16497-2");
MODULE_ALIAS("spi:adis16497-3");
