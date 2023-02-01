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

MODULE_INFO(staging, "Y");

MODULE_INFO(depends, "adt7316");

MODULE_ALIAS("of:N*T*Cadi,adt7316");
MODULE_ALIAS("of:N*T*Cadi,adt7316C*");
MODULE_ALIAS("of:N*T*Cadi,adt7317");
MODULE_ALIAS("of:N*T*Cadi,adt7317C*");
MODULE_ALIAS("of:N*T*Cadi,adt7318");
MODULE_ALIAS("of:N*T*Cadi,adt7318C*");
MODULE_ALIAS("of:N*T*Cadi,adt7516");
MODULE_ALIAS("of:N*T*Cadi,adt7516C*");
MODULE_ALIAS("of:N*T*Cadi,adt7517");
MODULE_ALIAS("of:N*T*Cadi,adt7517C*");
MODULE_ALIAS("of:N*T*Cadi,adt7519");
MODULE_ALIAS("of:N*T*Cadi,adt7519C*");
MODULE_ALIAS("spi:adt7316");
MODULE_ALIAS("spi:adt7317");
MODULE_ALIAS("spi:adt7318");
MODULE_ALIAS("spi:adt7516");
MODULE_ALIAS("spi:adt7517");
MODULE_ALIAS("spi:adt7519");
