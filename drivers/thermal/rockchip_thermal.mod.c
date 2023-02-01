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

MODULE_ALIAS("of:N*T*Crockchip,px30-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,px30-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-tsadcC*");
