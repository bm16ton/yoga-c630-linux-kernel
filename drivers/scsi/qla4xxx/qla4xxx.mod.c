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

MODULE_INFO(depends, "iscsi_boot_sysfs,scsi_transport_iscsi,libiscsi");

MODULE_ALIAS("pci:v00001077d00004010sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00004022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00004032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001077d00008042sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "0FE2FC84F862FEE5C7C093B");
