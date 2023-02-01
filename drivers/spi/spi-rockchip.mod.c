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

MODULE_ALIAS("of:N*T*Crockchip,px30-spi");
MODULE_ALIAS("of:N*T*Crockchip,px30-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3036-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3036-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3188-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3188-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3228-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3288-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3308-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3328-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3368-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-spi");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-spi");
MODULE_ALIAS("of:N*T*Crockchip,rv1108-spiC*");
MODULE_ALIAS("of:N*T*Crockchip,rv1126-spi");
MODULE_ALIAS("of:N*T*Crockchip,rv1126-spiC*");
