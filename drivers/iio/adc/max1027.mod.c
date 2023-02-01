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

MODULE_ALIAS("of:N*T*Cmaxim,max1027");
MODULE_ALIAS("of:N*T*Cmaxim,max1027C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1029");
MODULE_ALIAS("of:N*T*Cmaxim,max1029C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1031");
MODULE_ALIAS("of:N*T*Cmaxim,max1031C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1227");
MODULE_ALIAS("of:N*T*Cmaxim,max1227C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1229");
MODULE_ALIAS("of:N*T*Cmaxim,max1229C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1231");
MODULE_ALIAS("of:N*T*Cmaxim,max1231C*");
MODULE_ALIAS("spi:max1027");
MODULE_ALIAS("spi:max1029");
MODULE_ALIAS("spi:max1031");
MODULE_ALIAS("spi:max1227");
MODULE_ALIAS("spi:max1229");
MODULE_ALIAS("spi:max1231");
