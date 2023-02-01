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

MODULE_INFO(depends, "st_sensors,st_magn,industrialio,st_sensors_i2c");

MODULE_ALIAS("i2c:lsm303dlh_magn");
MODULE_ALIAS("i2c:lsm303dlhc_magn");
MODULE_ALIAS("i2c:lsm303dlm_magn");
MODULE_ALIAS("i2c:lis3mdl");
MODULE_ALIAS("i2c:lsm303agr_magn");
MODULE_ALIAS("i2c:lis2mdl");
MODULE_ALIAS("i2c:lsm9ds1_magn");
MODULE_ALIAS("i2c:iis2mdc");
MODULE_ALIAS("of:N*T*Cst,lsm303dlh-magn");
MODULE_ALIAS("of:N*T*Cst,lsm303dlh-magnC*");
MODULE_ALIAS("of:N*T*Cst,lsm303dlhc-magn");
MODULE_ALIAS("of:N*T*Cst,lsm303dlhc-magnC*");
MODULE_ALIAS("of:N*T*Cst,lsm303dlm-magn");
MODULE_ALIAS("of:N*T*Cst,lsm303dlm-magnC*");
MODULE_ALIAS("of:N*T*Cst,lis3mdl-magn");
MODULE_ALIAS("of:N*T*Cst,lis3mdl-magnC*");
MODULE_ALIAS("of:N*T*Cst,lsm303agr-magn");
MODULE_ALIAS("of:N*T*Cst,lsm303agr-magnC*");
MODULE_ALIAS("of:N*T*Cst,lis2mdl");
MODULE_ALIAS("of:N*T*Cst,lis2mdlC*");
MODULE_ALIAS("of:N*T*Cst,lsm9ds1-magn");
MODULE_ALIAS("of:N*T*Cst,lsm9ds1-magnC*");
MODULE_ALIAS("of:N*T*Cst,iis2mdc");
MODULE_ALIAS("of:N*T*Cst,iis2mdcC*");
