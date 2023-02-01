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

MODULE_ALIAS("of:N*T*Cqcom,sc7180-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sc7180-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sc7280-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sc8180x-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sc8280xp-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sc8280xp-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sdm845-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sm6350-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sm6350-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sm8150-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sm8250-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8350-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sm8350-llccC*");
MODULE_ALIAS("of:N*T*Cqcom,sm8450-llcc");
MODULE_ALIAS("of:N*T*Cqcom,sm8450-llccC*");
