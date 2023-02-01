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

MODULE_INFO(depends, "st_sensors,st_pressure,industrialio,st_sensors_spi");

MODULE_ALIAS("spi:lps001wp");
MODULE_ALIAS("spi:lps25h");
MODULE_ALIAS("spi:lps331ap");
MODULE_ALIAS("spi:lps22hb");
MODULE_ALIAS("spi:lps33hw");
MODULE_ALIAS("spi:lps35hw");
MODULE_ALIAS("spi:lps22hh");
MODULE_ALIAS("spi:lps22df");
MODULE_ALIAS("spi:lps001wp-press");
MODULE_ALIAS("spi:lps25h-press");
MODULE_ALIAS("spi:lps331ap-press");
MODULE_ALIAS("spi:lps22hb-press");
MODULE_ALIAS("of:N*T*Cst,lps001wp-press");
MODULE_ALIAS("of:N*T*Cst,lps001wp-pressC*");
MODULE_ALIAS("of:N*T*Cst,lps25h-press");
MODULE_ALIAS("of:N*T*Cst,lps25h-pressC*");
MODULE_ALIAS("of:N*T*Cst,lps331ap-press");
MODULE_ALIAS("of:N*T*Cst,lps331ap-pressC*");
MODULE_ALIAS("of:N*T*Cst,lps22hb-press");
MODULE_ALIAS("of:N*T*Cst,lps22hb-pressC*");
MODULE_ALIAS("of:N*T*Cst,lps33hw");
MODULE_ALIAS("of:N*T*Cst,lps33hwC*");
MODULE_ALIAS("of:N*T*Cst,lps35hw");
MODULE_ALIAS("of:N*T*Cst,lps35hwC*");
MODULE_ALIAS("of:N*T*Cst,lps22hh");
MODULE_ALIAS("of:N*T*Cst,lps22hhC*");
MODULE_ALIAS("of:N*T*Cst,lps22df");
MODULE_ALIAS("of:N*T*Cst,lps22dfC*");
