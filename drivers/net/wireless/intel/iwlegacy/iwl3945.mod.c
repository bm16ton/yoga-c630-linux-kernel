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

MODULE_INFO(depends, "iwlegacy,mac80211,cfg80211");

MODULE_ALIAS("pci:v00008086d00004222sv*sd00001005bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00004222sv*sd00001034bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00004222sv*sd00001044bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00004227sv*sd00001014bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00004222sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00008086d00004227sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "F7C7C865C2120FA587F88CA");
