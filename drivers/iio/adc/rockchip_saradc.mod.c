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

MODULE_INFO(depends, "industrialio,industrialio-triggered-buffer");

MODULE_ALIAS("of:N*T*Crockchip,saradc");
MODULE_ALIAS("of:N*T*Crockchip,saradcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-tsadc");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-tsadcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-saradc");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-saradcC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-saradc");
MODULE_ALIAS("of:N*T*Crockchip,rk3568-saradcC*");
