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

MODULE_INFO(depends, "bmc150-accel-core");

MODULE_ALIAS("of:N*T*Cbosch,bma222");
MODULE_ALIAS("of:N*T*Cbosch,bma222C*");
MODULE_ALIAS("of:N*T*Cbosch,bma222e");
MODULE_ALIAS("of:N*T*Cbosch,bma222eC*");
MODULE_ALIAS("of:N*T*Cbosch,bma250e");
MODULE_ALIAS("of:N*T*Cbosch,bma250eC*");
MODULE_ALIAS("of:N*T*Cbosch,bma253");
MODULE_ALIAS("of:N*T*Cbosch,bma253C*");
MODULE_ALIAS("of:N*T*Cbosch,bma254");
MODULE_ALIAS("of:N*T*Cbosch,bma254C*");
MODULE_ALIAS("of:N*T*Cbosch,bma255");
MODULE_ALIAS("of:N*T*Cbosch,bma255C*");
MODULE_ALIAS("of:N*T*Cbosch,bma280");
MODULE_ALIAS("of:N*T*Cbosch,bma280C*");
MODULE_ALIAS("of:N*T*Cbosch,bmc150_accel");
MODULE_ALIAS("of:N*T*Cbosch,bmc150_accelC*");
MODULE_ALIAS("of:N*T*Cbosch,bmc156_accel");
MODULE_ALIAS("of:N*T*Cbosch,bmc156_accelC*");
MODULE_ALIAS("of:N*T*Cbosch,bmi055_accel");
MODULE_ALIAS("of:N*T*Cbosch,bmi055_accelC*");
MODULE_ALIAS("i2c:bma222");
MODULE_ALIAS("i2c:bma222e");
MODULE_ALIAS("i2c:bma250e");
MODULE_ALIAS("i2c:bma253");
MODULE_ALIAS("i2c:bma254");
MODULE_ALIAS("i2c:bma255");
MODULE_ALIAS("i2c:bma280");
MODULE_ALIAS("i2c:bmc150_accel");
MODULE_ALIAS("i2c:bmc156_accel");
MODULE_ALIAS("i2c:bmi055_accel");
MODULE_ALIAS("acpi*:BMA0255:*");
MODULE_ALIAS("acpi*:BMA0280:*");
MODULE_ALIAS("acpi*:BMA222:*");
MODULE_ALIAS("acpi*:BMA222E:*");
MODULE_ALIAS("acpi*:BMA250E:*");
MODULE_ALIAS("acpi*:BMC150A:*");
MODULE_ALIAS("acpi*:BMI055A:*");
MODULE_ALIAS("acpi*:BOSC0200:*");
MODULE_ALIAS("acpi*:BSBA0150:*");
MODULE_ALIAS("acpi*:DUAL250E:*");
