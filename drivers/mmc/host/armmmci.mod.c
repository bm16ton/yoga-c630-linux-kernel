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

MODULE_ALIAS("amba:d00?41180");
MODULE_ALIAS("amba:d01?41180");
MODULE_ALIAS("amba:d02?41180");
MODULE_ALIAS("amba:d???41181");
MODULE_ALIAS("amba:d??180180");
MODULE_ALIAS("amba:d1?180180");
MODULE_ALIAS("amba:d??280180");
MODULE_ALIAS("amba:d0?480180");
MODULE_ALIAS("amba:d1?480180");
MODULE_ALIAS("amba:d??880180");
MODULE_ALIAS("amba:d1?153180");
MODULE_ALIAS("amba:d0?253180");
MODULE_ALIAS("amba:d2?253180");
MODULE_ALIAS("amba:d???51180");
