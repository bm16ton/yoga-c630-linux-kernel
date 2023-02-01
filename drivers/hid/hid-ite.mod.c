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

MODULE_ALIAS("hid:b0003g*v0000048Dp00008595");
MODULE_ALIAS("hid:b0003g*v0000258Ap00006A88");
MODULE_ALIAS("hid:b0003g0001v000006CBp00002968");
MODULE_ALIAS("hid:b0003g0001v000006CBp000073F4");
MODULE_ALIAS("hid:b0003g0001v000006CBp000073F5");
MODULE_ALIAS("hid:b0003g0001v000006CBp000073F6");
