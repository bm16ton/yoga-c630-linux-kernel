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

MODULE_ALIAS("of:N*T*Cmaxim,max7319");
MODULE_ALIAS("of:N*T*Cmaxim,max7319C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7320");
MODULE_ALIAS("of:N*T*Cmaxim,max7320C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7321");
MODULE_ALIAS("of:N*T*Cmaxim,max7321C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7322");
MODULE_ALIAS("of:N*T*Cmaxim,max7322C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7323");
MODULE_ALIAS("of:N*T*Cmaxim,max7323C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7324");
MODULE_ALIAS("of:N*T*Cmaxim,max7324C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7325");
MODULE_ALIAS("of:N*T*Cmaxim,max7325C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7326");
MODULE_ALIAS("of:N*T*Cmaxim,max7326C*");
MODULE_ALIAS("of:N*T*Cmaxim,max7327");
MODULE_ALIAS("of:N*T*Cmaxim,max7327C*");
MODULE_ALIAS("i2c:max7319");
MODULE_ALIAS("i2c:max7320");
MODULE_ALIAS("i2c:max7321");
MODULE_ALIAS("i2c:max7322");
MODULE_ALIAS("i2c:max7323");
MODULE_ALIAS("i2c:max7324");
MODULE_ALIAS("i2c:max7325");
MODULE_ALIAS("i2c:max7326");
MODULE_ALIAS("i2c:max7327");
