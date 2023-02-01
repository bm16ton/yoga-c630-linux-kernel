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

MODULE_INFO(depends, "ad5686");

MODULE_ALIAS("of:N*T*Cadi,ad5311r");
MODULE_ALIAS("of:N*T*Cadi,ad5311rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5338r");
MODULE_ALIAS("of:N*T*Cadi,ad5338rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5671r");
MODULE_ALIAS("of:N*T*Cadi,ad5671rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5675r");
MODULE_ALIAS("of:N*T*Cadi,ad5675rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5691r");
MODULE_ALIAS("of:N*T*Cadi,ad5691rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5692r");
MODULE_ALIAS("of:N*T*Cadi,ad5692rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5693");
MODULE_ALIAS("of:N*T*Cadi,ad5693C*");
MODULE_ALIAS("of:N*T*Cadi,ad5693r");
MODULE_ALIAS("of:N*T*Cadi,ad5693rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5694");
MODULE_ALIAS("of:N*T*Cadi,ad5694C*");
MODULE_ALIAS("of:N*T*Cadi,ad5694r");
MODULE_ALIAS("of:N*T*Cadi,ad5694rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5695r");
MODULE_ALIAS("of:N*T*Cadi,ad5695rC*");
MODULE_ALIAS("of:N*T*Cadi,ad5696");
MODULE_ALIAS("of:N*T*Cadi,ad5696C*");
MODULE_ALIAS("of:N*T*Cadi,ad5696r");
MODULE_ALIAS("of:N*T*Cadi,ad5696rC*");
MODULE_ALIAS("i2c:ad5311r");
MODULE_ALIAS("i2c:ad5338r");
MODULE_ALIAS("i2c:ad5671r");
MODULE_ALIAS("i2c:ad5673r");
MODULE_ALIAS("i2c:ad5675r");
MODULE_ALIAS("i2c:ad5677r");
MODULE_ALIAS("i2c:ad5691r");
MODULE_ALIAS("i2c:ad5692r");
MODULE_ALIAS("i2c:ad5693");
MODULE_ALIAS("i2c:ad5693r");
MODULE_ALIAS("i2c:ad5694");
MODULE_ALIAS("i2c:ad5694r");
MODULE_ALIAS("i2c:ad5695r");
MODULE_ALIAS("i2c:ad5696");
MODULE_ALIAS("i2c:ad5696r");
