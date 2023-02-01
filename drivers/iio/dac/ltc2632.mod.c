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

MODULE_ALIAS("of:N*T*Clltc,ltc2632-l12");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-l12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-l10");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-l10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-l8");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-l8C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h12");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h10");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h8");
MODULE_ALIAS("of:N*T*Clltc,ltc2632-h8C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l12");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l10");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l8");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-l8C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h12");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h10");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h8");
MODULE_ALIAS("of:N*T*Clltc,ltc2634-h8C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l12");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l10");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l8");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-l8C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h12");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h12C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h10");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h10C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h8");
MODULE_ALIAS("of:N*T*Clltc,ltc2636-h8C*");
MODULE_ALIAS("spi:ltc2632-l12");
MODULE_ALIAS("spi:ltc2632-l10");
MODULE_ALIAS("spi:ltc2632-l8");
MODULE_ALIAS("spi:ltc2632-h12");
MODULE_ALIAS("spi:ltc2632-h10");
MODULE_ALIAS("spi:ltc2632-h8");
MODULE_ALIAS("spi:ltc2634-l12");
MODULE_ALIAS("spi:ltc2634-l10");
MODULE_ALIAS("spi:ltc2634-l8");
MODULE_ALIAS("spi:ltc2634-h12");
MODULE_ALIAS("spi:ltc2634-h10");
MODULE_ALIAS("spi:ltc2634-h8");
MODULE_ALIAS("spi:ltc2636-l12");
MODULE_ALIAS("spi:ltc2636-l10");
MODULE_ALIAS("spi:ltc2636-l8");
MODULE_ALIAS("spi:ltc2636-h12");
MODULE_ALIAS("spi:ltc2636-h10");
MODULE_ALIAS("spi:ltc2636-h8");
