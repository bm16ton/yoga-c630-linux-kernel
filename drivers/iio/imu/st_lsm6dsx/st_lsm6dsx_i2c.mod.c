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

MODULE_INFO(depends, "st_lsm6dsx");

MODULE_ALIAS("i2c:lsm6ds3");
MODULE_ALIAS("i2c:lsm6ds3h");
MODULE_ALIAS("i2c:lsm6dsl");
MODULE_ALIAS("i2c:lsm6dsm");
MODULE_ALIAS("i2c:ism330dlc");
MODULE_ALIAS("i2c:lsm6dso");
MODULE_ALIAS("i2c:asm330lhh");
MODULE_ALIAS("i2c:lsm6dsox");
MODULE_ALIAS("i2c:lsm6dsr");
MODULE_ALIAS("i2c:lsm6ds3tr-c");
MODULE_ALIAS("i2c:ism330dhcx");
MODULE_ALIAS("i2c:lsm9ds1-imu");
MODULE_ALIAS("i2c:lsm6ds0");
MODULE_ALIAS("i2c:lsm6dsrx");
MODULE_ALIAS("i2c:lsm6dst");
MODULE_ALIAS("i2c:lsm6dsop");
MODULE_ALIAS("i2c:asm330lhhx");
MODULE_ALIAS("i2c:lsm6dstx");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3C*");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3h");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3hC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsl");
MODULE_ALIAS("of:N*T*Cst,lsm6dslC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsm");
MODULE_ALIAS("of:N*T*Cst,lsm6dsmC*");
MODULE_ALIAS("of:N*T*Cst,ism330dlc");
MODULE_ALIAS("of:N*T*Cst,ism330dlcC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dso");
MODULE_ALIAS("of:N*T*Cst,lsm6dsoC*");
MODULE_ALIAS("of:N*T*Cst,asm330lhh");
MODULE_ALIAS("of:N*T*Cst,asm330lhhC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsox");
MODULE_ALIAS("of:N*T*Cst,lsm6dsoxC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsr");
MODULE_ALIAS("of:N*T*Cst,lsm6dsrC*");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3tr-c");
MODULE_ALIAS("of:N*T*Cst,lsm6ds3tr-cC*");
MODULE_ALIAS("of:N*T*Cst,ism330dhcx");
MODULE_ALIAS("of:N*T*Cst,ism330dhcxC*");
MODULE_ALIAS("of:N*T*Cst,lsm9ds1-imu");
MODULE_ALIAS("of:N*T*Cst,lsm9ds1-imuC*");
MODULE_ALIAS("of:N*T*Cst,lsm6ds0");
MODULE_ALIAS("of:N*T*Cst,lsm6ds0C*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsrx");
MODULE_ALIAS("of:N*T*Cst,lsm6dsrxC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dst");
MODULE_ALIAS("of:N*T*Cst,lsm6dstC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dsop");
MODULE_ALIAS("of:N*T*Cst,lsm6dsopC*");
MODULE_ALIAS("of:N*T*Cst,asm330lhhx");
MODULE_ALIAS("of:N*T*Cst,asm330lhhxC*");
MODULE_ALIAS("of:N*T*Cst,lsm6dstx");
MODULE_ALIAS("of:N*T*Cst,lsm6dstxC*");
