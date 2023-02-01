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

MODULE_INFO(depends, "hwmon-vid");

MODULE_ALIAS("of:N*T*Cadi,adm1027");
MODULE_ALIAS("of:N*T*Cadi,adm1027C*");
MODULE_ALIAS("of:N*T*Cadi,adt7463");
MODULE_ALIAS("of:N*T*Cadi,adt7463C*");
MODULE_ALIAS("of:N*T*Cadi,adt7468");
MODULE_ALIAS("of:N*T*Cadi,adt7468C*");
MODULE_ALIAS("of:N*T*Cnational,lm85");
MODULE_ALIAS("of:N*T*Cnational,lm85C*");
MODULE_ALIAS("of:N*T*Cnational,lm85b");
MODULE_ALIAS("of:N*T*Cnational,lm85bC*");
MODULE_ALIAS("of:N*T*Cnational,lm85c");
MODULE_ALIAS("of:N*T*Cnational,lm85cC*");
MODULE_ALIAS("of:N*T*Cti,lm96000");
MODULE_ALIAS("of:N*T*Cti,lm96000C*");
MODULE_ALIAS("of:N*T*Csmsc,emc6d100");
MODULE_ALIAS("of:N*T*Csmsc,emc6d100C*");
MODULE_ALIAS("of:N*T*Csmsc,emc6d101");
MODULE_ALIAS("of:N*T*Csmsc,emc6d101C*");
MODULE_ALIAS("of:N*T*Csmsc,emc6d102");
MODULE_ALIAS("of:N*T*Csmsc,emc6d102C*");
MODULE_ALIAS("of:N*T*Csmsc,emc6d103");
MODULE_ALIAS("of:N*T*Csmsc,emc6d103C*");
MODULE_ALIAS("of:N*T*Csmsc,emc6d103s");
MODULE_ALIAS("of:N*T*Csmsc,emc6d103sC*");
MODULE_ALIAS("i2c:adm1027");
MODULE_ALIAS("i2c:adt7463");
MODULE_ALIAS("i2c:adt7468");
MODULE_ALIAS("i2c:lm85");
MODULE_ALIAS("i2c:lm85b");
MODULE_ALIAS("i2c:lm85c");
MODULE_ALIAS("i2c:lm96000");
MODULE_ALIAS("i2c:emc6d100");
MODULE_ALIAS("i2c:emc6d101");
MODULE_ALIAS("i2c:emc6d102");
MODULE_ALIAS("i2c:emc6d103");
MODULE_ALIAS("i2c:emc6d103s");
