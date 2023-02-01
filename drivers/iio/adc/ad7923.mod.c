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

MODULE_INFO(depends, "industrialio,industrialio-triggered-buffer");

MODULE_ALIAS("of:N*T*Cadi,ad7904");
MODULE_ALIAS("of:N*T*Cadi,ad7904C*");
MODULE_ALIAS("of:N*T*Cadi,ad7914");
MODULE_ALIAS("of:N*T*Cadi,ad7914C*");
MODULE_ALIAS("of:N*T*Cadi,ad7923");
MODULE_ALIAS("of:N*T*Cadi,ad7923C*");
MODULE_ALIAS("of:N*T*Cadi,ad7924");
MODULE_ALIAS("of:N*T*Cadi,ad7924C*");
MODULE_ALIAS("of:N*T*Cadi,ad7908");
MODULE_ALIAS("of:N*T*Cadi,ad7908C*");
MODULE_ALIAS("of:N*T*Cadi,ad7918");
MODULE_ALIAS("of:N*T*Cadi,ad7918C*");
MODULE_ALIAS("of:N*T*Cadi,ad7928");
MODULE_ALIAS("of:N*T*Cadi,ad7928C*");
MODULE_ALIAS("spi:ad7904");
MODULE_ALIAS("spi:ad7914");
MODULE_ALIAS("spi:ad7923");
MODULE_ALIAS("spi:ad7924");
MODULE_ALIAS("spi:ad7908");
MODULE_ALIAS("spi:ad7918");
MODULE_ALIAS("spi:ad7928");
