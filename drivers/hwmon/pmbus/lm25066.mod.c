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

MODULE_ALIAS("of:N*T*Cti,lm25056");
MODULE_ALIAS("of:N*T*Cti,lm25056C*");
MODULE_ALIAS("of:N*T*Cti,lm25066");
MODULE_ALIAS("of:N*T*Cti,lm25066C*");
MODULE_ALIAS("of:N*T*Cti,lm5064");
MODULE_ALIAS("of:N*T*Cti,lm5064C*");
MODULE_ALIAS("of:N*T*Cti,lm5066");
MODULE_ALIAS("of:N*T*Cti,lm5066C*");
MODULE_ALIAS("of:N*T*Cti,lm5066i");
MODULE_ALIAS("of:N*T*Cti,lm5066iC*");
MODULE_ALIAS("i2c:lm25056");
MODULE_ALIAS("i2c:lm25066");
MODULE_ALIAS("i2c:lm5064");
MODULE_ALIAS("i2c:lm5066");
MODULE_ALIAS("i2c:lm5066i");
