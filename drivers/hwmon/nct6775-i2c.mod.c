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

MODULE_INFO(depends, "nct6775-core");

MODULE_ALIAS("i2c:nct6106");
MODULE_ALIAS("i2c:nct6116");
MODULE_ALIAS("i2c:nct6775");
MODULE_ALIAS("i2c:nct6776");
MODULE_ALIAS("i2c:nct6779");
MODULE_ALIAS("i2c:nct6791");
MODULE_ALIAS("i2c:nct6792");
MODULE_ALIAS("i2c:nct6793");
MODULE_ALIAS("i2c:nct6795");
MODULE_ALIAS("i2c:nct6796");
MODULE_ALIAS("i2c:nct6797");
MODULE_ALIAS("i2c:nct6798");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6106");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6106C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6116");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6116C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6775");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6775C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6776");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6776C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6779");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6779C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6791");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6791C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6792");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6792C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6793");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6793C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6795");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6795C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6796");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6796C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6797");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6797C*");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6798");
MODULE_ALIAS("of:N*T*Cnuvoton,nct6798C*");
