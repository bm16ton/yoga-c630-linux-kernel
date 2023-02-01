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

MODULE_ALIAS("spi:lm70");
MODULE_ALIAS("spi:tmp121");
MODULE_ALIAS("spi:tmp122");
MODULE_ALIAS("spi:tmp125");
MODULE_ALIAS("spi:lm71");
MODULE_ALIAS("spi:lm74");
MODULE_ALIAS("of:N*T*Cti,lm70");
MODULE_ALIAS("of:N*T*Cti,lm70C*");
MODULE_ALIAS("of:N*T*Cti,tmp121");
MODULE_ALIAS("of:N*T*Cti,tmp121C*");
MODULE_ALIAS("of:N*T*Cti,tmp122");
MODULE_ALIAS("of:N*T*Cti,tmp122C*");
MODULE_ALIAS("of:N*T*Cti,tmp125");
MODULE_ALIAS("of:N*T*Cti,tmp125C*");
MODULE_ALIAS("of:N*T*Cti,lm71");
MODULE_ALIAS("of:N*T*Cti,lm71C*");
MODULE_ALIAS("of:N*T*Cti,lm74");
MODULE_ALIAS("of:N*T*Cti,lm74C*");
