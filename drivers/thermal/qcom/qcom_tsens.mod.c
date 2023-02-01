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

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cqcom,ipq8064-tsens");
MODULE_ALIAS("of:N*T*Cqcom,ipq8064-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,mdm9607-tsens");
MODULE_ALIAS("of:N*T*Cqcom,mdm9607-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8916-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8916-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8939-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8939-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8960-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8960-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8974-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8974-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8976-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8976-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-tsens");
MODULE_ALIAS("of:N*T*Cqcom,msm8996-tsensC*");
MODULE_ALIAS("of:N*T*Cqcom,tsens-v1");
MODULE_ALIAS("of:N*T*Cqcom,tsens-v1C*");
MODULE_ALIAS("of:N*T*Cqcom,tsens-v2");
MODULE_ALIAS("of:N*T*Cqcom,tsens-v2C*");
