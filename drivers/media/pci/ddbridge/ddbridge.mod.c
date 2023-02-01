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

MODULE_INFO(depends, "dvb-core");

MODULE_ALIAS("pci:v0000DD01d00000002sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000003sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000005sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000006sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000007sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000008sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000009sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000011sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000012sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000013sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000201sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000203sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000210sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000220sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000320sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000321sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000322sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000323sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000328sv0000DD01sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000DD01d00000329sv0000DD01sd*bc*sc*i*");

MODULE_INFO(srcversion, "789C8E53B1AC1CDE12C1172");
