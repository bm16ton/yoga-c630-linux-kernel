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

MODULE_INFO(depends, "libata");

MODULE_ALIAS("pci:v000010FCd00000003sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001145d00008008sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001145d0000F008sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001145d0000F021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001145d0000F024sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001145d0000F02Csv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "42B160F106BBB8062CC31D5");
