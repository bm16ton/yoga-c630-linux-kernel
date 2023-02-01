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

MODULE_ALIAS("pci:v00001148d00009000sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001148d00009E00sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001148d00009E01sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004B00sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004B02sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004B03sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004340sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004341sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004342sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004343sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004344sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004345sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004346sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004347sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004350sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004351sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004352sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004353sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004354sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004355sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004356sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004357sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd0000435Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004360sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004361sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004362sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004363sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004364sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004365sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004366sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004367sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004368sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004369sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd0000436Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd0000436Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd0000436Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd0000436Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004370sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004380sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004381sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000011ABd00004382sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "1C3CA0439903B426BFBEDA8");
