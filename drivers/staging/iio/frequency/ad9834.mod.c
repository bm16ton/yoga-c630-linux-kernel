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

MODULE_INFO(staging, "Y");

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("of:N*T*Cadi,ad9833");
MODULE_ALIAS("of:N*T*Cadi,ad9833C*");
MODULE_ALIAS("of:N*T*Cadi,ad9834");
MODULE_ALIAS("of:N*T*Cadi,ad9834C*");
MODULE_ALIAS("of:N*T*Cadi,ad9837");
MODULE_ALIAS("of:N*T*Cadi,ad9837C*");
MODULE_ALIAS("of:N*T*Cadi,ad9838");
MODULE_ALIAS("of:N*T*Cadi,ad9838C*");
MODULE_ALIAS("spi:ad9833");
MODULE_ALIAS("spi:ad9834");
MODULE_ALIAS("spi:ad9837");
MODULE_ALIAS("spi:ad9838");
