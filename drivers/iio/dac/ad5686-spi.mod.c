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

MODULE_INFO(depends, "ad5686");

MODULE_ALIAS("spi:ad5310r");
MODULE_ALIAS("spi:ad5672r");
MODULE_ALIAS("spi:ad5674r");
MODULE_ALIAS("spi:ad5676");
MODULE_ALIAS("spi:ad5676r");
MODULE_ALIAS("spi:ad5679r");
MODULE_ALIAS("spi:ad5681r");
MODULE_ALIAS("spi:ad5682r");
MODULE_ALIAS("spi:ad5683");
MODULE_ALIAS("spi:ad5683r");
MODULE_ALIAS("spi:ad5684");
MODULE_ALIAS("spi:ad5684r");
MODULE_ALIAS("spi:ad5685");
MODULE_ALIAS("spi:ad5685r");
MODULE_ALIAS("spi:ad5686");
MODULE_ALIAS("spi:ad5686r");
