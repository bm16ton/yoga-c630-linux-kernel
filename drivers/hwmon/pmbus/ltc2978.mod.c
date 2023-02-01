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

MODULE_ALIAS("of:N*T*Clltc,ltc2972");
MODULE_ALIAS("of:N*T*Clltc,ltc2972C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2974");
MODULE_ALIAS("of:N*T*Clltc,ltc2974C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2975");
MODULE_ALIAS("of:N*T*Clltc,ltc2975C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2977");
MODULE_ALIAS("of:N*T*Clltc,ltc2977C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2978");
MODULE_ALIAS("of:N*T*Clltc,ltc2978C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2979");
MODULE_ALIAS("of:N*T*Clltc,ltc2979C*");
MODULE_ALIAS("of:N*T*Clltc,ltc2980");
MODULE_ALIAS("of:N*T*Clltc,ltc2980C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3880");
MODULE_ALIAS("of:N*T*Clltc,ltc3880C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3882");
MODULE_ALIAS("of:N*T*Clltc,ltc3882C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3883");
MODULE_ALIAS("of:N*T*Clltc,ltc3883C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3884");
MODULE_ALIAS("of:N*T*Clltc,ltc3884C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3886");
MODULE_ALIAS("of:N*T*Clltc,ltc3886C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3887");
MODULE_ALIAS("of:N*T*Clltc,ltc3887C*");
MODULE_ALIAS("of:N*T*Clltc,ltc3889");
MODULE_ALIAS("of:N*T*Clltc,ltc3889C*");
MODULE_ALIAS("of:N*T*Clltc,ltc7880");
MODULE_ALIAS("of:N*T*Clltc,ltc7880C*");
MODULE_ALIAS("of:N*T*Clltc,ltm2987");
MODULE_ALIAS("of:N*T*Clltc,ltm2987C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4664");
MODULE_ALIAS("of:N*T*Clltc,ltm4664C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4675");
MODULE_ALIAS("of:N*T*Clltc,ltm4675C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4676");
MODULE_ALIAS("of:N*T*Clltc,ltm4676C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4677");
MODULE_ALIAS("of:N*T*Clltc,ltm4677C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4678");
MODULE_ALIAS("of:N*T*Clltc,ltm4678C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4680");
MODULE_ALIAS("of:N*T*Clltc,ltm4680C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4686");
MODULE_ALIAS("of:N*T*Clltc,ltm4686C*");
MODULE_ALIAS("of:N*T*Clltc,ltm4700");
MODULE_ALIAS("of:N*T*Clltc,ltm4700C*");
MODULE_ALIAS("i2c:ltc2972");
MODULE_ALIAS("i2c:ltc2974");
MODULE_ALIAS("i2c:ltc2975");
MODULE_ALIAS("i2c:ltc2977");
MODULE_ALIAS("i2c:ltc2978");
MODULE_ALIAS("i2c:ltc2979");
MODULE_ALIAS("i2c:ltc2980");
MODULE_ALIAS("i2c:ltc3880");
MODULE_ALIAS("i2c:ltc3882");
MODULE_ALIAS("i2c:ltc3883");
MODULE_ALIAS("i2c:ltc3884");
MODULE_ALIAS("i2c:ltc3886");
MODULE_ALIAS("i2c:ltc3887");
MODULE_ALIAS("i2c:ltc3889");
MODULE_ALIAS("i2c:ltc7880");
MODULE_ALIAS("i2c:ltm2987");
MODULE_ALIAS("i2c:ltm4664");
MODULE_ALIAS("i2c:ltm4675");
MODULE_ALIAS("i2c:ltm4676");
MODULE_ALIAS("i2c:ltm4677");
MODULE_ALIAS("i2c:ltm4678");
MODULE_ALIAS("i2c:ltm4680");
MODULE_ALIAS("i2c:ltm4686");
MODULE_ALIAS("i2c:ltm4700");
