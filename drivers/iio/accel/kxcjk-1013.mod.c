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

MODULE_ALIAS("of:N*T*Ckionix,kxcjk1013");
MODULE_ALIAS("of:N*T*Ckionix,kxcjk1013C*");
MODULE_ALIAS("of:N*T*Ckionix,kxcj91008");
MODULE_ALIAS("of:N*T*Ckionix,kxcj91008C*");
MODULE_ALIAS("of:N*T*Ckionix,kxtj21009");
MODULE_ALIAS("of:N*T*Ckionix,kxtj21009C*");
MODULE_ALIAS("of:N*T*Ckionix,kxtf9");
MODULE_ALIAS("of:N*T*Ckionix,kxtf9C*");
MODULE_ALIAS("of:N*T*Ckionix,kx023-1025");
MODULE_ALIAS("of:N*T*Ckionix,kx023-1025C*");
MODULE_ALIAS("i2c:kxcjk1013");
MODULE_ALIAS("i2c:kxcj91008");
MODULE_ALIAS("i2c:kxtj21009");
MODULE_ALIAS("i2c:kxtf9");
MODULE_ALIAS("i2c:kx023-1025");
MODULE_ALIAS("i2c:SMO8500");
MODULE_ALIAS("acpi*:KXCJ1013:*");
MODULE_ALIAS("acpi*:KXCJ1008:*");
MODULE_ALIAS("acpi*:KXCJ9000:*");
MODULE_ALIAS("acpi*:KIOX0008:*");
MODULE_ALIAS("acpi*:KIOX0009:*");
MODULE_ALIAS("acpi*:KIOX000A:*");
MODULE_ALIAS("acpi*:KIOX010A:*");
MODULE_ALIAS("acpi*:KIOX020A:*");
MODULE_ALIAS("acpi*:KXTJ1009:*");
MODULE_ALIAS("acpi*:KXJ2109:*");
MODULE_ALIAS("acpi*:SMO8500:*");
