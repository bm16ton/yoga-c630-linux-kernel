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

MODULE_ALIAS("i2c:dtt7579");
MODULE_ALIAS("i2c:dtt759x");
MODULE_ALIAS("i2c:z201");
MODULE_ALIAS("i2c:unknown_1");
MODULE_ALIAS("i2c:tua6010xs");
MODULE_ALIAS("i2c:env57h1xd5");
MODULE_ALIAS("i2c:tua6034");
MODULE_ALIAS("i2c:tda665x");
MODULE_ALIAS("i2c:tded4");
MODULE_ALIAS("i2c:tdhu2");
MODULE_ALIAS("i2c:tbmv");
MODULE_ALIAS("i2c:sd1878_tda8261");
MODULE_ALIAS("i2c:opera1");
MODULE_ALIAS("i2c:dtos403ih102a");
MODULE_ALIAS("i2c:tdtc9251dh0");
MODULE_ALIAS("i2c:tbdu18132");
MODULE_ALIAS("i2c:tbmu24112");
MODULE_ALIAS("i2c:tdee4");
MODULE_ALIAS("i2c:dtt7520x");
MODULE_ALIAS("i2c:tua6034_friio");
MODULE_ALIAS("i2c:tda665x_earthpt1");
