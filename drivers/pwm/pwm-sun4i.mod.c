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

MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a10s-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a10s-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-pwmC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-pwm");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-pwmC*");
