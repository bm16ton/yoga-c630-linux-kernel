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

MODULE_ALIAS("of:N*T*Cwinbond,w83781d");
MODULE_ALIAS("of:N*T*Cwinbond,w83781dC*");
MODULE_ALIAS("of:N*T*Cwinbond,w83781g");
MODULE_ALIAS("of:N*T*Cwinbond,w83781gC*");
MODULE_ALIAS("of:N*T*Cwinbond,w83782d");
MODULE_ALIAS("of:N*T*Cwinbond,w83782dC*");
MODULE_ALIAS("of:N*T*Cwinbond,w83783s");
MODULE_ALIAS("of:N*T*Cwinbond,w83783sC*");
MODULE_ALIAS("of:N*T*Casus,as99127f");
MODULE_ALIAS("of:N*T*Casus,as99127fC*");
MODULE_ALIAS("i2c:w83781d");
MODULE_ALIAS("i2c:w83782d");
MODULE_ALIAS("i2c:w83783s");
MODULE_ALIAS("i2c:as99127f");
