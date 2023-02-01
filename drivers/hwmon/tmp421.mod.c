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

MODULE_ALIAS("of:N*T*Cti,tmp421");
MODULE_ALIAS("of:N*T*Cti,tmp421C*");
MODULE_ALIAS("of:N*T*Cti,tmp422");
MODULE_ALIAS("of:N*T*Cti,tmp422C*");
MODULE_ALIAS("of:N*T*Cti,tmp423");
MODULE_ALIAS("of:N*T*Cti,tmp423C*");
MODULE_ALIAS("of:N*T*Cti,tmp441");
MODULE_ALIAS("of:N*T*Cti,tmp441C*");
MODULE_ALIAS("of:N*T*Cti,tmp442");
MODULE_ALIAS("of:N*T*Cti,tmp442C*");
MODULE_ALIAS("i2c:tmp421");
MODULE_ALIAS("i2c:tmp422");
MODULE_ALIAS("i2c:tmp423");
MODULE_ALIAS("i2c:tmp441");
MODULE_ALIAS("i2c:tmp442");
