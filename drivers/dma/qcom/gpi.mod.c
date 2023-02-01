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
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cqcom,sc7280-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sm6350-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sm6350-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8350-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sm8350-gpi-dmaC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8450-gpi-dma");
MODULE_ALIAS("of:N*T*Cqcom,sm8450-gpi-dmaC*");
