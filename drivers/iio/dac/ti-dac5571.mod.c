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

MODULE_ALIAS("i2c:dac5571");
MODULE_ALIAS("i2c:dac6571");
MODULE_ALIAS("i2c:dac7571");
MODULE_ALIAS("i2c:dac5574");
MODULE_ALIAS("i2c:dac6574");
MODULE_ALIAS("i2c:dac7574");
MODULE_ALIAS("i2c:dac5573");
MODULE_ALIAS("i2c:dac6573");
MODULE_ALIAS("i2c:dac7573");
MODULE_ALIAS("i2c:dac121c081");
MODULE_ALIAS("of:N*T*Cti,dac5571");
MODULE_ALIAS("of:N*T*Cti,dac5571C*");
MODULE_ALIAS("of:N*T*Cti,dac6571");
MODULE_ALIAS("of:N*T*Cti,dac6571C*");
MODULE_ALIAS("of:N*T*Cti,dac7571");
MODULE_ALIAS("of:N*T*Cti,dac7571C*");
MODULE_ALIAS("of:N*T*Cti,dac5574");
MODULE_ALIAS("of:N*T*Cti,dac5574C*");
MODULE_ALIAS("of:N*T*Cti,dac6574");
MODULE_ALIAS("of:N*T*Cti,dac6574C*");
MODULE_ALIAS("of:N*T*Cti,dac7574");
MODULE_ALIAS("of:N*T*Cti,dac7574C*");
MODULE_ALIAS("of:N*T*Cti,dac5573");
MODULE_ALIAS("of:N*T*Cti,dac5573C*");
MODULE_ALIAS("of:N*T*Cti,dac6573");
MODULE_ALIAS("of:N*T*Cti,dac6573C*");
MODULE_ALIAS("of:N*T*Cti,dac7573");
MODULE_ALIAS("of:N*T*Cti,dac7573C*");
MODULE_ALIAS("of:N*T*Cti,dac121c081");
MODULE_ALIAS("of:N*T*Cti,dac121c081C*");
