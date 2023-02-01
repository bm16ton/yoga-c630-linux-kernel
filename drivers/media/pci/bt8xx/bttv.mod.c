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

MODULE_INFO(depends, "videobuf-core,videodev,tea575x,i2c-algo-bit,videobuf-dma-sg,rc-core,tveeprom");

MODULE_ALIAS("pci:v0000109Ed00000350sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000109Ed00000351sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000109Ed0000036Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000109Ed0000036Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000109Ed0000036Csv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "08B186A201BD06BF51F29AA");
