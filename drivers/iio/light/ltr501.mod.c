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

MODULE_INFO(depends, "industrialio,industrialio-triggered-buffer");

MODULE_ALIAS("of:N*T*Cliteon,ltr501");
MODULE_ALIAS("of:N*T*Cliteon,ltr501C*");
MODULE_ALIAS("of:N*T*Cliteon,ltr559");
MODULE_ALIAS("of:N*T*Cliteon,ltr559C*");
MODULE_ALIAS("of:N*T*Cliteon,ltr301");
MODULE_ALIAS("of:N*T*Cliteon,ltr301C*");
MODULE_ALIAS("of:N*T*Cliteon,ltr303");
MODULE_ALIAS("of:N*T*Cliteon,ltr303C*");
MODULE_ALIAS("i2c:ltr501");
MODULE_ALIAS("i2c:ltr559");
MODULE_ALIAS("i2c:ltr301");
MODULE_ALIAS("i2c:ltr303");
MODULE_ALIAS("acpi*:LTER0501:*");
MODULE_ALIAS("acpi*:LTER0559:*");
MODULE_ALIAS("acpi*:LTER0301:*");
