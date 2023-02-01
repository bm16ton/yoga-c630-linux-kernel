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

MODULE_ALIAS("of:N*T*Callwinner,sun6i-a31-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun6i-a31-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a23-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a23-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a83t-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-v3s-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-v3s-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a100-dmaC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-dma");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-dmaC*");
