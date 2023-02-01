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

MODULE_INFO(depends, "drm,drm_kms_helper,drm_display_helper,gpu-sched,ocmem,llcc-qcom,drm_dp_aux_bus,mdt_loader");

MODULE_ALIAS("of:N*T*Cqcom,msm8998-dpu");
MODULE_ALIAS("of:N*T*Cqcom,msm8998-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,qcm2290-dpu");
MODULE_ALIAS("of:N*T*Cqcom,qcm2290-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-dpu");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-dpuC*");
MODULE_ALIAS("of:N*T*Cqcom,mdp4");
MODULE_ALIAS("of:N*T*Cqcom,mdp4C*");
MODULE_ALIAS("of:N*T*Cqcom,mdp5");
MODULE_ALIAS("of:N*T*Cqcom,mdp5C*");
MODULE_ALIAS("of:N*T*Cqcom,mdss_mdp");
MODULE_ALIAS("of:N*T*Cqcom,mdss_mdpC*");
MODULE_ALIAS("of:N*T*Cqcom,mdss");
MODULE_ALIAS("of:N*T*Cqcom,mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8998-mdss");
MODULE_ALIAS("of:N*T*Cqcom,msm8998-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,qcm2290-mdss");
MODULE_ALIAS("of:N*T*Cqcom,qcm2290-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-mdssC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-mdss");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-mdssC*");
