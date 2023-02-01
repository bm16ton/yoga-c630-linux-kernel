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

MODULE_INFO(depends, "cavium_ptp");

MODULE_ALIAS("pci:v0000177Dd0000A034sv0000177Dsd0000A134bc*sc*i*");
MODULE_ALIAS("pci:v0000177Dd00000011sv0000177Dsd0000A11Ebc*sc*i*");
MODULE_ALIAS("pci:v0000177Dd0000A034sv0000177Dsd0000A234bc*sc*i*");
MODULE_ALIAS("pci:v0000177Dd0000A034sv0000177Dsd0000A334bc*sc*i*");

MODULE_INFO(srcversion, "5EC3BAEF6E72D6F9F590240");
