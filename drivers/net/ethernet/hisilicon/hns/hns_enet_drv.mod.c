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

MODULE_INFO(depends, "libphy,hnae");

MODULE_ALIAS("of:N*T*Chisilicon,hns-nic-v1");
MODULE_ALIAS("of:N*T*Chisilicon,hns-nic-v1C*");
MODULE_ALIAS("of:N*T*Chisilicon,hns-nic-v2");
MODULE_ALIAS("of:N*T*Chisilicon,hns-nic-v2C*");
MODULE_ALIAS("acpi*:HISI00C1:*");
MODULE_ALIAS("acpi*:HISI00C2:*");
