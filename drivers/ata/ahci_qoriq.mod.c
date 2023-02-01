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

MODULE_INFO(depends, "libata,libahci,libahci_platform");

MODULE_ALIAS("acpi*:NXP0004:*");
MODULE_ALIAS("of:N*T*Cfsl,ls1021a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls1021a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls1028a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls1028a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls1043a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls1043a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls2080a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls2080a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls1046a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls1046a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls1088a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls1088a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,ls2088a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,ls2088a-ahciC*");
MODULE_ALIAS("of:N*T*Cfsl,lx2160a-ahci");
MODULE_ALIAS("of:N*T*Cfsl,lx2160a-ahciC*");
