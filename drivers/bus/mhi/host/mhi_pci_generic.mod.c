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

MODULE_INFO(depends, "mhi");

MODULE_ALIAS("pci:v000017CBd00000304sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000017CBd00000306sv000018D7sd00000200bc*sc*i*");
MODULE_ALIAS("pci:v000017CBd00000306sv00001C5Dsd00002000bc*sc*i*");
MODULE_ALIAS("pci:v000017CBd00000306sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000017CBd00000308sv00001C5Dsd00002010bc*sc*i*");
MODULE_ALIAS("pci:v000017CBd00000308sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001EACd00001001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001EACd00001002sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001EACd00002001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0ABsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0B0sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0B1sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0BFsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0C3sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0D8sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000105Bd0000E0D9sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001269d000000B3sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001269d000000B4sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001269d000000BAsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001269d000000BBsv*sd*bc*sc*i*");
