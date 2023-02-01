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

MODULE_INFO(depends, "libphy,hnae3,mdio_devres");

MODULE_ALIAS("pci:v000019E5d0000A220sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A221sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A222sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A223sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A224sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A225sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A226sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000019E5d0000A228sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "81879ACE6EA1EC6FE801B7F");
