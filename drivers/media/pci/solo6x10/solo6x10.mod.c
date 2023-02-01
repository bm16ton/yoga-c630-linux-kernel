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

MODULE_INFO(depends, "videobuf2-v4l2,videobuf2-dma-sg,videodev,snd,snd-pcm,videobuf2-dma-contig,videobuf2-common");

MODULE_ALIAS("pci:v00009413d00006010sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004304sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004309sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004310sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004E04sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004E09sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00004E10sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00009413d00006110sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00005304sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00005308sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001BB3d00005310sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "32D1D8416E19CAF66BB60FF");
