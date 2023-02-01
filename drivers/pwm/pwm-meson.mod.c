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

MODULE_ALIAS("of:N*T*Camlogic,meson8b-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson8b-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-ao-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-ao-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-axg-ee-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson-axg-ee-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-axg-ao-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson-axg-ao-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ee-pwm");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ee-pwmC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ao-pwm-ab");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ao-pwm-abC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ao-pwm-cd");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-ao-pwm-cdC*");
