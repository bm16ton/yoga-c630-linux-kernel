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
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

MODULE_INFO(depends, "nand");

MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v2.1");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v2.1C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v2.2");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v2.2C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v4.0");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v4.0C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v5.0");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v5.0C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.0");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.0C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.1");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.1C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.2");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v6.2C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.0");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.0C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.1");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.1C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.2");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.2C*");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.3");
MODULE_ALIAS("of:N*T*Cbrcm,brcmnand-v7.3C*");
