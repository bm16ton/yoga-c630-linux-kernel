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

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("acpi*:AANT1280:*");
MODULE_ALIAS("spi:adc128s052");
MODULE_ALIAS("spi:adc122s021");
MODULE_ALIAS("spi:adc122s051");
MODULE_ALIAS("spi:adc122s101");
MODULE_ALIAS("spi:adc124s021");
MODULE_ALIAS("spi:adc124s051");
MODULE_ALIAS("spi:adc124s101");
MODULE_ALIAS("of:N*T*Cti,adc128s052");
MODULE_ALIAS("of:N*T*Cti,adc128s052C*");
MODULE_ALIAS("of:N*T*Cti,adc122s021");
MODULE_ALIAS("of:N*T*Cti,adc122s021C*");
MODULE_ALIAS("of:N*T*Cti,adc122s051");
MODULE_ALIAS("of:N*T*Cti,adc122s051C*");
MODULE_ALIAS("of:N*T*Cti,adc122s101");
MODULE_ALIAS("of:N*T*Cti,adc122s101C*");
MODULE_ALIAS("of:N*T*Cti,adc124s021");
MODULE_ALIAS("of:N*T*Cti,adc124s021C*");
MODULE_ALIAS("of:N*T*Cti,adc124s051");
MODULE_ALIAS("of:N*T*Cti,adc124s051C*");
MODULE_ALIAS("of:N*T*Cti,adc124s101");
MODULE_ALIAS("of:N*T*Cti,adc124s101C*");
