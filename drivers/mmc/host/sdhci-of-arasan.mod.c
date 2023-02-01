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

MODULE_INFO(depends, "sdhci,cqhci,sdhci-pltfm");

MODULE_ALIAS("of:N*T*Crockchip,rk3399-sdhci-5.1");
MODULE_ALIAS("of:N*T*Crockchip,rk3399-sdhci-5.1C*");
MODULE_ALIAS("of:N*T*Cintel,lgm-sdhci-5.1-emmc");
MODULE_ALIAS("of:N*T*Cintel,lgm-sdhci-5.1-emmcC*");
MODULE_ALIAS("of:N*T*Cintel,lgm-sdhci-5.1-sdxc");
MODULE_ALIAS("of:N*T*Cintel,lgm-sdhci-5.1-sdxcC*");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-emmc");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-emmcC*");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-sd");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-sdC*");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-sdio");
MODULE_ALIAS("of:N*T*Cintel,keembay-sdhci-5.1-sdioC*");
MODULE_ALIAS("of:N*T*Cintel,thunderbay-sdhci-5.1");
MODULE_ALIAS("of:N*T*Cintel,thunderbay-sdhci-5.1C*");
MODULE_ALIAS("of:N*T*Carasan,sdhci-8.9a");
MODULE_ALIAS("of:N*T*Carasan,sdhci-8.9aC*");
MODULE_ALIAS("of:N*T*Carasan,sdhci-5.1");
MODULE_ALIAS("of:N*T*Carasan,sdhci-5.1C*");
MODULE_ALIAS("of:N*T*Carasan,sdhci-4.9a");
MODULE_ALIAS("of:N*T*Carasan,sdhci-4.9aC*");
MODULE_ALIAS("of:N*T*Cxlnx,zynqmp-8.9a");
MODULE_ALIAS("of:N*T*Cxlnx,zynqmp-8.9aC*");
MODULE_ALIAS("of:N*T*Cxlnx,versal-8.9a");
MODULE_ALIAS("of:N*T*Cxlnx,versal-8.9aC*");
