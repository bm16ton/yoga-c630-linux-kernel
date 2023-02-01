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

MODULE_ALIAS("hid:b0003g*v0000172Fp00000032");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000034");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000037");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000038");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000501");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000500");
MODULE_ALIAS("hid:b0003g*v0000172Fp00000502");
