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

MODULE_ALIAS("pci:v00008086d00001591sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001592sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001593sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001599sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000159Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000159Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000188Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000188Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000188Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000188Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000188Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001890sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001891sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001892sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001893sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001894sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001897sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001898sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001899sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000189Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000124Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000124Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000124Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000124Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000151Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00001888sv*sd*bc*sc*i*");
