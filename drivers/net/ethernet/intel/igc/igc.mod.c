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

MODULE_ALIAS("pci:v00008086d000015F2sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015F3sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015F8sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015F7sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00003100sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00003101sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00003102sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00005502sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00005503sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00000D9Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000125Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000125Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000125Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000125Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d0000125Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d000015FDsv*sd*bc*sc*i*");
