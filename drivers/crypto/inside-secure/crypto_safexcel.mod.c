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

MODULE_INFO(depends, "authenc,libdes");

MODULE_ALIAS("pci:v000010EEd00009038sv000016AEsd0000C522bc*sc*i*");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip97ies");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip97iesC*");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197b");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197bC*");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197d");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197dC*");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip97");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip97C*");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197");
MODULE_ALIAS("of:N*T*Cinside-secure,safexcel-eip197C*");
