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

MODULE_INFO(depends, "stmmac,stmmac-platform");

MODULE_ALIAS("of:N*T*Crockchip,px30-gmac");
MODULE_ALIAS("of:N*T*Crockchip,px30-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3128-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3128-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3366-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3588-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rk3588-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-gmacC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1126-gmac");
MODULE_ALIAS("of:N*T*Crockchip,rv1126-gmacC*");
