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

MODULE_INFO(depends, "v4l2-mem2mem,videobuf2-common,mdt_loader,videodev");

MODULE_ALIAS("of:N*T*Cqcom,msm8916-venus");
MODULE_ALIAS("of:N*T*Cqcom,msm8916-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-venus");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm660-venus");
MODULE_ALIAS("of:N*T*Cqcom,sdm660-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-venus");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-venus-v2");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-venus-v2C*");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-venus");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-venus");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-venusC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-venus");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-venusC*");
