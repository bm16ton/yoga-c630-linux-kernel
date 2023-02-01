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

MODULE_INFO(depends, "pmbus_core");

MODULE_ALIAS("i2c:isl68137");
MODULE_ALIAS("i2c:isl68220");
MODULE_ALIAS("i2c:isl68221");
MODULE_ALIAS("i2c:isl68222");
MODULE_ALIAS("i2c:isl68223");
MODULE_ALIAS("i2c:isl68224");
MODULE_ALIAS("i2c:isl68225");
MODULE_ALIAS("i2c:isl68226");
MODULE_ALIAS("i2c:isl68227");
MODULE_ALIAS("i2c:isl68229");
MODULE_ALIAS("i2c:isl68233");
MODULE_ALIAS("i2c:isl68239");
MODULE_ALIAS("i2c:isl69222");
MODULE_ALIAS("i2c:isl69223");
MODULE_ALIAS("i2c:isl69224");
MODULE_ALIAS("i2c:isl69225");
MODULE_ALIAS("i2c:isl69227");
MODULE_ALIAS("i2c:isl69228");
MODULE_ALIAS("i2c:isl69234");
MODULE_ALIAS("i2c:isl69236");
MODULE_ALIAS("i2c:isl69239");
MODULE_ALIAS("i2c:isl69242");
MODULE_ALIAS("i2c:isl69243");
MODULE_ALIAS("i2c:isl69247");
MODULE_ALIAS("i2c:isl69248");
MODULE_ALIAS("i2c:isl69254");
MODULE_ALIAS("i2c:isl69255");
MODULE_ALIAS("i2c:isl69256");
MODULE_ALIAS("i2c:isl69259");
MODULE_ALIAS("i2c:isl69260");
MODULE_ALIAS("i2c:isl69268");
MODULE_ALIAS("i2c:isl69269");
MODULE_ALIAS("i2c:isl69298");
MODULE_ALIAS("i2c:raa228000");
MODULE_ALIAS("i2c:raa228004");
MODULE_ALIAS("i2c:raa228006");
MODULE_ALIAS("i2c:raa228228");
MODULE_ALIAS("i2c:raa229001");
MODULE_ALIAS("i2c:raa229004");
