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

MODULE_ALIAS("of:N*T*Cepcos,b57330v2103");
MODULE_ALIAS("of:N*T*Cepcos,b57330v2103C*");
MODULE_ALIAS("of:N*T*Cepcos,b57891s0103");
MODULE_ALIAS("of:N*T*Cepcos,b57891s0103C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp03wb473");
MODULE_ALIAS("of:N*T*Cmurata,ncp03wb473C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp03wf104");
MODULE_ALIAS("of:N*T*Cmurata,ncp03wf104C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp15wb473");
MODULE_ALIAS("of:N*T*Cmurata,ncp15wb473C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp15wl333");
MODULE_ALIAS("of:N*T*Cmurata,ncp15wl333C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp15xh103");
MODULE_ALIAS("of:N*T*Cmurata,ncp15xh103C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp18wb473");
MODULE_ALIAS("of:N*T*Cmurata,ncp18wb473C*");
MODULE_ALIAS("of:N*T*Cmurata,ncp21wb473");
MODULE_ALIAS("of:N*T*Cmurata,ncp21wb473C*");
MODULE_ALIAS("of:N*T*Csamsung,1404-001221");
MODULE_ALIAS("of:N*T*Csamsung,1404-001221C*");
MODULE_ALIAS("of:N*T*Cntc,ncp03wb473");
MODULE_ALIAS("of:N*T*Cntc,ncp03wb473C*");
MODULE_ALIAS("of:N*T*Cntc,ncp15wb473");
MODULE_ALIAS("of:N*T*Cntc,ncp15wb473C*");
MODULE_ALIAS("of:N*T*Cntc,ncp15wl333");
MODULE_ALIAS("of:N*T*Cntc,ncp15wl333C*");
MODULE_ALIAS("of:N*T*Cntc,ncp18wb473");
MODULE_ALIAS("of:N*T*Cntc,ncp18wb473C*");
MODULE_ALIAS("of:N*T*Cntc,ncp21wb473");
MODULE_ALIAS("of:N*T*Cntc,ncp21wb473C*");
