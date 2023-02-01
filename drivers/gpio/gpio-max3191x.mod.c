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

MODULE_ALIAS("spi:max31910");
MODULE_ALIAS("spi:max31911");
MODULE_ALIAS("spi:max31912");
MODULE_ALIAS("spi:max31913");
MODULE_ALIAS("spi:max31953");
MODULE_ALIAS("spi:max31963");
MODULE_ALIAS("of:N*T*Cmaxim,max31910");
MODULE_ALIAS("of:N*T*Cmaxim,max31910C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31911");
MODULE_ALIAS("of:N*T*Cmaxim,max31911C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31912");
MODULE_ALIAS("of:N*T*Cmaxim,max31912C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31913");
MODULE_ALIAS("of:N*T*Cmaxim,max31913C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31953");
MODULE_ALIAS("of:N*T*Cmaxim,max31953C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31963");
MODULE_ALIAS("of:N*T*Cmaxim,max31963C*");
