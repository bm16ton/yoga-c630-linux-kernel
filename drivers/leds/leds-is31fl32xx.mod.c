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

MODULE_ALIAS("i2c:is31fl3236");
MODULE_ALIAS("i2c:is31fl3235");
MODULE_ALIAS("i2c:is31fl3218");
MODULE_ALIAS("i2c:sn3218");
MODULE_ALIAS("i2c:is31fl3216");
MODULE_ALIAS("i2c:sn3216");
MODULE_ALIAS("of:N*T*Cissi,is31fl3236");
MODULE_ALIAS("of:N*T*Cissi,is31fl3236C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3235");
MODULE_ALIAS("of:N*T*Cissi,is31fl3235C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3218");
MODULE_ALIAS("of:N*T*Cissi,is31fl3218C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3218");
MODULE_ALIAS("of:N*T*Csi-en,sn3218C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3216");
MODULE_ALIAS("of:N*T*Cissi,is31fl3216C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3216");
MODULE_ALIAS("of:N*T*Csi-en,sn3216C*");
