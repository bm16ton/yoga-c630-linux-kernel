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

MODULE_INFO(staging, "Y");

MODULE_INFO(depends, "v4l2-mem2mem,videobuf2-v4l2,videodev,mc,videobuf2-dma-contig,videobuf2-common");

MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun4i-a10-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun5i-a13-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun7i-a20-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a33-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-a33-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-h3-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-v3s-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-v3s-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-a64-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h5-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h5-video-engineC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-video-engine");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-video-engineC*");
