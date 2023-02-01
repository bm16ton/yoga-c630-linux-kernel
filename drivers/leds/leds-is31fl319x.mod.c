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

MODULE_ALIAS("i2c:is31fl3190");
MODULE_ALIAS("i2c:is31fl3191");
MODULE_ALIAS("i2c:is31fl3193");
MODULE_ALIAS("i2c:is31fl3196");
MODULE_ALIAS("i2c:is31fl3199");
MODULE_ALIAS("i2c:sn3190");
MODULE_ALIAS("i2c:sn3191");
MODULE_ALIAS("i2c:sn3193");
MODULE_ALIAS("i2c:sn3196");
MODULE_ALIAS("i2c:sn3199");
MODULE_ALIAS("of:N*T*Cissi,is31fl3190");
MODULE_ALIAS("of:N*T*Cissi,is31fl3190C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3191");
MODULE_ALIAS("of:N*T*Cissi,is31fl3191C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3193");
MODULE_ALIAS("of:N*T*Cissi,is31fl3193C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3196");
MODULE_ALIAS("of:N*T*Cissi,is31fl3196C*");
MODULE_ALIAS("of:N*T*Cissi,is31fl3199");
MODULE_ALIAS("of:N*T*Cissi,is31fl3199C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3190");
MODULE_ALIAS("of:N*T*Csi-en,sn3190C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3191");
MODULE_ALIAS("of:N*T*Csi-en,sn3191C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3193");
MODULE_ALIAS("of:N*T*Csi-en,sn3193C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3196");
MODULE_ALIAS("of:N*T*Csi-en,sn3196C*");
MODULE_ALIAS("of:N*T*Csi-en,sn3199");
MODULE_ALIAS("of:N*T*Csi-en,sn3199C*");
