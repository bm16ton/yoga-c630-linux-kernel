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

MODULE_INFO(depends, "industrialio,industrialio-triggered-buffer");

MODULE_ALIAS("i2c:max1361");
MODULE_ALIAS("i2c:max1362");
MODULE_ALIAS("i2c:max1363");
MODULE_ALIAS("i2c:max1364");
MODULE_ALIAS("i2c:max1036");
MODULE_ALIAS("i2c:max1037");
MODULE_ALIAS("i2c:max1038");
MODULE_ALIAS("i2c:max1039");
MODULE_ALIAS("i2c:max1136");
MODULE_ALIAS("i2c:max1137");
MODULE_ALIAS("i2c:max1138");
MODULE_ALIAS("i2c:max1139");
MODULE_ALIAS("i2c:max1236");
MODULE_ALIAS("i2c:max1237");
MODULE_ALIAS("i2c:max1238");
MODULE_ALIAS("i2c:max1239");
MODULE_ALIAS("i2c:max11600");
MODULE_ALIAS("i2c:max11601");
MODULE_ALIAS("i2c:max11602");
MODULE_ALIAS("i2c:max11603");
MODULE_ALIAS("i2c:max11604");
MODULE_ALIAS("i2c:max11605");
MODULE_ALIAS("i2c:max11606");
MODULE_ALIAS("i2c:max11607");
MODULE_ALIAS("i2c:max11608");
MODULE_ALIAS("i2c:max11609");
MODULE_ALIAS("i2c:max11610");
MODULE_ALIAS("i2c:max11611");
MODULE_ALIAS("i2c:max11612");
MODULE_ALIAS("i2c:max11613");
MODULE_ALIAS("i2c:max11614");
MODULE_ALIAS("i2c:max11615");
MODULE_ALIAS("i2c:max11616");
MODULE_ALIAS("i2c:max11617");
MODULE_ALIAS("i2c:max11644");
MODULE_ALIAS("i2c:max11645");
MODULE_ALIAS("i2c:max11646");
MODULE_ALIAS("i2c:max11647");
MODULE_ALIAS("of:N*T*Cmaxim,max1361");
MODULE_ALIAS("of:N*T*Cmaxim,max1361C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1362");
MODULE_ALIAS("of:N*T*Cmaxim,max1362C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1363");
MODULE_ALIAS("of:N*T*Cmaxim,max1363C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1364");
MODULE_ALIAS("of:N*T*Cmaxim,max1364C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1036");
MODULE_ALIAS("of:N*T*Cmaxim,max1036C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1037");
MODULE_ALIAS("of:N*T*Cmaxim,max1037C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1038");
MODULE_ALIAS("of:N*T*Cmaxim,max1038C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1039");
MODULE_ALIAS("of:N*T*Cmaxim,max1039C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1136");
MODULE_ALIAS("of:N*T*Cmaxim,max1136C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1137");
MODULE_ALIAS("of:N*T*Cmaxim,max1137C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1138");
MODULE_ALIAS("of:N*T*Cmaxim,max1138C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1139");
MODULE_ALIAS("of:N*T*Cmaxim,max1139C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1236");
MODULE_ALIAS("of:N*T*Cmaxim,max1236C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1237");
MODULE_ALIAS("of:N*T*Cmaxim,max1237C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1238");
MODULE_ALIAS("of:N*T*Cmaxim,max1238C*");
MODULE_ALIAS("of:N*T*Cmaxim,max1239");
MODULE_ALIAS("of:N*T*Cmaxim,max1239C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11600");
MODULE_ALIAS("of:N*T*Cmaxim,max11600C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11601");
MODULE_ALIAS("of:N*T*Cmaxim,max11601C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11602");
MODULE_ALIAS("of:N*T*Cmaxim,max11602C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11603");
MODULE_ALIAS("of:N*T*Cmaxim,max11603C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11604");
MODULE_ALIAS("of:N*T*Cmaxim,max11604C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11605");
MODULE_ALIAS("of:N*T*Cmaxim,max11605C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11606");
MODULE_ALIAS("of:N*T*Cmaxim,max11606C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11607");
MODULE_ALIAS("of:N*T*Cmaxim,max11607C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11608");
MODULE_ALIAS("of:N*T*Cmaxim,max11608C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11609");
MODULE_ALIAS("of:N*T*Cmaxim,max11609C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11610");
MODULE_ALIAS("of:N*T*Cmaxim,max11610C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11611");
MODULE_ALIAS("of:N*T*Cmaxim,max11611C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11612");
MODULE_ALIAS("of:N*T*Cmaxim,max11612C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11613");
MODULE_ALIAS("of:N*T*Cmaxim,max11613C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11614");
MODULE_ALIAS("of:N*T*Cmaxim,max11614C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11615");
MODULE_ALIAS("of:N*T*Cmaxim,max11615C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11616");
MODULE_ALIAS("of:N*T*Cmaxim,max11616C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11617");
MODULE_ALIAS("of:N*T*Cmaxim,max11617C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11644");
MODULE_ALIAS("of:N*T*Cmaxim,max11644C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11645");
MODULE_ALIAS("of:N*T*Cmaxim,max11645C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11646");
MODULE_ALIAS("of:N*T*Cmaxim,max11646C*");
MODULE_ALIAS("of:N*T*Cmaxim,max11647");
MODULE_ALIAS("of:N*T*Cmaxim,max11647C*");
