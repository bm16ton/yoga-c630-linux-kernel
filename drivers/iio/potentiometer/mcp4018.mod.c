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

MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-502");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-502C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-103");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-103C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-503");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-503C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-104");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4017-104C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-502");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-502C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-103");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-103C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-503");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-503C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-104");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4018-104C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-502");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-502C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-103");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-103C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-503");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-503C*");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-104");
MODULE_ALIAS("of:N*T*Cmicrochip,mcp4019-104C*");
MODULE_ALIAS("i2c:mcp4017-502");
MODULE_ALIAS("i2c:mcp4017-103");
MODULE_ALIAS("i2c:mcp4017-503");
MODULE_ALIAS("i2c:mcp4017-104");
MODULE_ALIAS("i2c:mcp4018-502");
MODULE_ALIAS("i2c:mcp4018-103");
MODULE_ALIAS("i2c:mcp4018-503");
MODULE_ALIAS("i2c:mcp4018-104");
MODULE_ALIAS("i2c:mcp4019-502");
MODULE_ALIAS("i2c:mcp4019-103");
MODULE_ALIAS("i2c:mcp4019-503");
MODULE_ALIAS("i2c:mcp4019-104");
