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

MODULE_ALIAS("of:N*T*Cti,ads7950");
MODULE_ALIAS("of:N*T*Cti,ads7950C*");
MODULE_ALIAS("of:N*T*Cti,ads7951");
MODULE_ALIAS("of:N*T*Cti,ads7951C*");
MODULE_ALIAS("of:N*T*Cti,ads7952");
MODULE_ALIAS("of:N*T*Cti,ads7952C*");
MODULE_ALIAS("of:N*T*Cti,ads7953");
MODULE_ALIAS("of:N*T*Cti,ads7953C*");
MODULE_ALIAS("of:N*T*Cti,ads7954");
MODULE_ALIAS("of:N*T*Cti,ads7954C*");
MODULE_ALIAS("of:N*T*Cti,ads7955");
MODULE_ALIAS("of:N*T*Cti,ads7955C*");
MODULE_ALIAS("of:N*T*Cti,ads7956");
MODULE_ALIAS("of:N*T*Cti,ads7956C*");
MODULE_ALIAS("of:N*T*Cti,ads7957");
MODULE_ALIAS("of:N*T*Cti,ads7957C*");
MODULE_ALIAS("of:N*T*Cti,ads7958");
MODULE_ALIAS("of:N*T*Cti,ads7958C*");
MODULE_ALIAS("of:N*T*Cti,ads7959");
MODULE_ALIAS("of:N*T*Cti,ads7959C*");
MODULE_ALIAS("of:N*T*Cti,ads7960");
MODULE_ALIAS("of:N*T*Cti,ads7960C*");
MODULE_ALIAS("of:N*T*Cti,ads7961");
MODULE_ALIAS("of:N*T*Cti,ads7961C*");
MODULE_ALIAS("spi:ads7950");
MODULE_ALIAS("spi:ads7951");
MODULE_ALIAS("spi:ads7952");
MODULE_ALIAS("spi:ads7953");
MODULE_ALIAS("spi:ads7954");
MODULE_ALIAS("spi:ads7955");
MODULE_ALIAS("spi:ads7956");
MODULE_ALIAS("spi:ads7957");
MODULE_ALIAS("spi:ads7958");
MODULE_ALIAS("spi:ads7959");
MODULE_ALIAS("spi:ads7960");
MODULE_ALIAS("spi:ads7961");
