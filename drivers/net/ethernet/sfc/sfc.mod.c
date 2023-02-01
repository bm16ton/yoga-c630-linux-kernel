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

MODULE_INFO(depends, "mdio");

MODULE_ALIAS("pci:v000010EEd00000100sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00001100sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00000903sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00001903sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00000923sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00001923sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00000A03sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00001A03sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00000B03sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001924d00001B03sv*sd*bc*sc*i*");
