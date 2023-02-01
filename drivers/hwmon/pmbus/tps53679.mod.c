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

MODULE_INFO(depends, "pmbus_core");

MODULE_ALIAS("of:N*T*Cti,tps53647");
MODULE_ALIAS("of:N*T*Cti,tps53647C*");
MODULE_ALIAS("of:N*T*Cti,tps53667");
MODULE_ALIAS("of:N*T*Cti,tps53667C*");
MODULE_ALIAS("of:N*T*Cti,tps53676");
MODULE_ALIAS("of:N*T*Cti,tps53676C*");
MODULE_ALIAS("of:N*T*Cti,tps53679");
MODULE_ALIAS("of:N*T*Cti,tps53679C*");
MODULE_ALIAS("of:N*T*Cti,tps53681");
MODULE_ALIAS("of:N*T*Cti,tps53681C*");
MODULE_ALIAS("of:N*T*Cti,tps53688");
MODULE_ALIAS("of:N*T*Cti,tps53688C*");
MODULE_ALIAS("i2c:bmr474");
MODULE_ALIAS("i2c:tps53647");
MODULE_ALIAS("i2c:tps53667");
MODULE_ALIAS("i2c:tps53676");
MODULE_ALIAS("i2c:tps53679");
MODULE_ALIAS("i2c:tps53681");
MODULE_ALIAS("i2c:tps53688");
