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

MODULE_INFO(depends, "ssd130x");

MODULE_ALIAS("spi:sh1106");
MODULE_ALIAS("spi:ssd1305");
MODULE_ALIAS("spi:ssd1306");
MODULE_ALIAS("spi:ssd1307");
MODULE_ALIAS("spi:ssd1309");
MODULE_ALIAS("of:N*T*Csinowealth,sh1106");
MODULE_ALIAS("of:N*T*Csinowealth,sh1106C*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1305");
MODULE_ALIAS("of:N*T*Csolomon,ssd1305C*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1306");
MODULE_ALIAS("of:N*T*Csolomon,ssd1306C*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1307");
MODULE_ALIAS("of:N*T*Csolomon,ssd1307C*");
MODULE_ALIAS("of:N*T*Csolomon,ssd1309");
MODULE_ALIAS("of:N*T*Csolomon,ssd1309C*");
