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

MODULE_INFO(depends, "scsi_transport_fc,nvme-fc");

MODULE_ALIAS("pci:v00001077d00002100sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002200sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002300sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002312sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002322sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00006312sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00006322sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002422sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002432sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008432sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00005422sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00005432sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002532sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002031sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008031sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d0000F001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008044sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002071sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002271sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002261sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002061sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002081sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002281sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002089sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00002289sv*sd*bc*sc*i*");
