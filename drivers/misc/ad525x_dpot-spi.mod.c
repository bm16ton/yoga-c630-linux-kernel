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

MODULE_INFO(depends, "ad525x_dpot");

MODULE_ALIAS("spi:ad5160");
MODULE_ALIAS("spi:ad5161");
MODULE_ALIAS("spi:ad5162");
MODULE_ALIAS("spi:ad5165");
MODULE_ALIAS("spi:ad5200");
MODULE_ALIAS("spi:ad5201");
MODULE_ALIAS("spi:ad5203");
MODULE_ALIAS("spi:ad5204");
MODULE_ALIAS("spi:ad5206");
MODULE_ALIAS("spi:ad5207");
MODULE_ALIAS("spi:ad5231");
MODULE_ALIAS("spi:ad5232");
MODULE_ALIAS("spi:ad5233");
MODULE_ALIAS("spi:ad5235");
MODULE_ALIAS("spi:ad5260");
MODULE_ALIAS("spi:ad5262");
MODULE_ALIAS("spi:ad5263");
MODULE_ALIAS("spi:ad5290");
MODULE_ALIAS("spi:ad5291");
MODULE_ALIAS("spi:ad5292");
MODULE_ALIAS("spi:ad5293");
MODULE_ALIAS("spi:ad7376");
MODULE_ALIAS("spi:ad8400");
MODULE_ALIAS("spi:ad8402");
MODULE_ALIAS("spi:ad8403");
MODULE_ALIAS("spi:adn2850");
MODULE_ALIAS("spi:ad5270");
MODULE_ALIAS("spi:ad5271");
