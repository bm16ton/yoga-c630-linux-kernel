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

MODULE_INFO(depends, "qcom_q6v5,qcom_sysmon,qcom_common,qcom_pil_info,mdt_loader");

MODULE_ALIAS("of:N*T*Cqcom,q6v5-pil");
MODULE_ALIAS("of:N*T*Cqcom,q6v5-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8916-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,msm8916-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8974-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,msm8974-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8998-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,msm8998-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-mss-pilC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-mss-pil");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-mss-pilC*");
