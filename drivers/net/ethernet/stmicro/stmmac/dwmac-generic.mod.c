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

MODULE_INFO(depends, "stmmac-platform,stmmac");

MODULE_ALIAS("of:N*T*Cst,spear600-gmac");
MODULE_ALIAS("of:N*T*Cst,spear600-gmacC*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.40a");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.40aC*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.50a");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.50aC*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.610");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.610C*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.70a");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.70aC*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.710");
MODULE_ALIAS("of:N*T*Csnps,dwmac-3.710C*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-4.00");
MODULE_ALIAS("of:N*T*Csnps,dwmac-4.00C*");
MODULE_ALIAS("of:N*T*Csnps,dwmac-4.10a");
MODULE_ALIAS("of:N*T*Csnps,dwmac-4.10aC*");
MODULE_ALIAS("of:N*T*Csnps,dwmac");
MODULE_ALIAS("of:N*T*Csnps,dwmacC*");
MODULE_ALIAS("of:N*T*Csnps,dwxgmac-2.10");
MODULE_ALIAS("of:N*T*Csnps,dwxgmac-2.10C*");
MODULE_ALIAS("of:N*T*Csnps,dwxgmac");
MODULE_ALIAS("of:N*T*Csnps,dwxgmacC*");
