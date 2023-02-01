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

MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-emmc");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-emmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun9i-a80-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun9i-a80-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-emmc");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-emmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-mmc");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-mmcC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-emmc");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-emmcC*");
