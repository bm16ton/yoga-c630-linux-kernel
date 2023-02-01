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

MODULE_ALIAS("of:N*T*Cmaxim,max6675");
MODULE_ALIAS("of:N*T*Cmaxim,max6675C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855");
MODULE_ALIAS("of:N*T*Cmaxim,max31855C*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855k");
MODULE_ALIAS("of:N*T*Cmaxim,max31855kC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855j");
MODULE_ALIAS("of:N*T*Cmaxim,max31855jC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855n");
MODULE_ALIAS("of:N*T*Cmaxim,max31855nC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855s");
MODULE_ALIAS("of:N*T*Cmaxim,max31855sC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855t");
MODULE_ALIAS("of:N*T*Cmaxim,max31855tC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855e");
MODULE_ALIAS("of:N*T*Cmaxim,max31855eC*");
MODULE_ALIAS("of:N*T*Cmaxim,max31855r");
MODULE_ALIAS("of:N*T*Cmaxim,max31855rC*");
MODULE_ALIAS("spi:max6675");
MODULE_ALIAS("spi:max31855");
MODULE_ALIAS("spi:max31855k");
MODULE_ALIAS("spi:max31855j");
MODULE_ALIAS("spi:max31855n");
MODULE_ALIAS("spi:max31855s");
MODULE_ALIAS("spi:max31855t");
MODULE_ALIAS("spi:max31855e");
MODULE_ALIAS("spi:max31855r");
