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

MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h5-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h5-thsC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-ths");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-thsC*");
