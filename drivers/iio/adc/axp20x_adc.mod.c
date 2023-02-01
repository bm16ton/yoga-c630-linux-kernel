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

MODULE_ALIAS("platform:axp20x-adc");
MODULE_ALIAS("platform:axp22x-adc");
MODULE_ALIAS("platform:axp813-adc");
MODULE_ALIAS("of:N*T*Cx-powers,axp209-adc");
MODULE_ALIAS("of:N*T*Cx-powers,axp209-adcC*");
MODULE_ALIAS("of:N*T*Cx-powers,axp221-adc");
MODULE_ALIAS("of:N*T*Cx-powers,axp221-adcC*");
MODULE_ALIAS("of:N*T*Cx-powers,axp813-adc");
MODULE_ALIAS("of:N*T*Cx-powers,axp813-adcC*");
