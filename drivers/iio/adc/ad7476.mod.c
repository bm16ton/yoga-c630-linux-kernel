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

MODULE_INFO(depends, "industrialio,industrialio-triggered-buffer");

MODULE_ALIAS("spi:ad7091");
MODULE_ALIAS("spi:ad7091r");
MODULE_ALIAS("spi:ad7273");
MODULE_ALIAS("spi:ad7274");
MODULE_ALIAS("spi:ad7276");
MODULE_ALIAS("spi:ad7277");
MODULE_ALIAS("spi:ad7278");
MODULE_ALIAS("spi:ad7466");
MODULE_ALIAS("spi:ad7467");
MODULE_ALIAS("spi:ad7468");
MODULE_ALIAS("spi:ad7475");
MODULE_ALIAS("spi:ad7476");
MODULE_ALIAS("spi:ad7476a");
MODULE_ALIAS("spi:ad7477");
MODULE_ALIAS("spi:ad7477a");
MODULE_ALIAS("spi:ad7478");
MODULE_ALIAS("spi:ad7478a");
MODULE_ALIAS("spi:ad7495");
MODULE_ALIAS("spi:ad7910");
MODULE_ALIAS("spi:ad7920");
MODULE_ALIAS("spi:ad7940");
MODULE_ALIAS("spi:adc081s");
MODULE_ALIAS("spi:adc101s");
MODULE_ALIAS("spi:adc121s");
MODULE_ALIAS("spi:ads7866");
MODULE_ALIAS("spi:ads7867");
MODULE_ALIAS("spi:ads7868");
MODULE_ALIAS("spi:ltc2314-14");
