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

MODULE_ALIAS("spi:eeprom-93xx46");
MODULE_ALIAS("spi:at93c46");
MODULE_ALIAS("spi:at93c46d");
MODULE_ALIAS("spi:at93c56");
MODULE_ALIAS("spi:at93c66");
MODULE_ALIAS("spi:93lc46b");
MODULE_ALIAS("of:N*T*Ceeprom-93xx46");
MODULE_ALIAS("of:N*T*Ceeprom-93xx46C*");
MODULE_ALIAS("of:N*T*Catmel,at93c46");
MODULE_ALIAS("of:N*T*Catmel,at93c46C*");
MODULE_ALIAS("of:N*T*Catmel,at93c46d");
MODULE_ALIAS("of:N*T*Catmel,at93c46dC*");
MODULE_ALIAS("of:N*T*Catmel,at93c56");
MODULE_ALIAS("of:N*T*Catmel,at93c56C*");
MODULE_ALIAS("of:N*T*Catmel,at93c66");
MODULE_ALIAS("of:N*T*Catmel,at93c66C*");
MODULE_ALIAS("of:N*T*Cmicrochip,93lc46b");
MODULE_ALIAS("of:N*T*Cmicrochip,93lc46bC*");
