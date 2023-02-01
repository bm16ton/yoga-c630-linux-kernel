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

MODULE_INFO(depends, "drm,gpu-sched,drm_shmem_helper");

MODULE_ALIAS("of:N*T*Camlogic,meson-gxm-mali");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxm-maliC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-mali");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-maliC*");
MODULE_ALIAS("of:N*T*Carm,mali-t604");
MODULE_ALIAS("of:N*T*Carm,mali-t604C*");
MODULE_ALIAS("of:N*T*Carm,mali-t624");
MODULE_ALIAS("of:N*T*Carm,mali-t624C*");
MODULE_ALIAS("of:N*T*Carm,mali-t628");
MODULE_ALIAS("of:N*T*Carm,mali-t628C*");
MODULE_ALIAS("of:N*T*Carm,mali-t720");
MODULE_ALIAS("of:N*T*Carm,mali-t720C*");
MODULE_ALIAS("of:N*T*Carm,mali-t760");
MODULE_ALIAS("of:N*T*Carm,mali-t760C*");
MODULE_ALIAS("of:N*T*Carm,mali-t820");
MODULE_ALIAS("of:N*T*Carm,mali-t820C*");
MODULE_ALIAS("of:N*T*Carm,mali-t830");
MODULE_ALIAS("of:N*T*Carm,mali-t830C*");
MODULE_ALIAS("of:N*T*Carm,mali-t860");
MODULE_ALIAS("of:N*T*Carm,mali-t860C*");
MODULE_ALIAS("of:N*T*Carm,mali-t880");
MODULE_ALIAS("of:N*T*Carm,mali-t880C*");
MODULE_ALIAS("of:N*T*Carm,mali-bifrost");
MODULE_ALIAS("of:N*T*Carm,mali-bifrostC*");
MODULE_ALIAS("of:N*T*Carm,mali-valhall-jm");
MODULE_ALIAS("of:N*T*Carm,mali-valhall-jmC*");
MODULE_ALIAS("of:N*T*Cmediatek,mt8183-mali");
MODULE_ALIAS("of:N*T*Cmediatek,mt8183-maliC*");
