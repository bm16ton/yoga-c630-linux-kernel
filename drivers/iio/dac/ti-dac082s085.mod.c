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

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("spi:dac082s085");
MODULE_ALIAS("spi:dac102s085");
MODULE_ALIAS("spi:dac122s085");
MODULE_ALIAS("spi:dac084s085");
MODULE_ALIAS("spi:dac104s085");
MODULE_ALIAS("spi:dac124s085");
MODULE_ALIAS("of:N*T*Cti,dac082s085");
MODULE_ALIAS("of:N*T*Cti,dac082s085C*");
MODULE_ALIAS("of:N*T*Cti,dac102s085");
MODULE_ALIAS("of:N*T*Cti,dac102s085C*");
MODULE_ALIAS("of:N*T*Cti,dac122s085");
MODULE_ALIAS("of:N*T*Cti,dac122s085C*");
MODULE_ALIAS("of:N*T*Cti,dac084s085");
MODULE_ALIAS("of:N*T*Cti,dac084s085C*");
MODULE_ALIAS("of:N*T*Cti,dac104s085");
MODULE_ALIAS("of:N*T*Cti,dac104s085C*");
MODULE_ALIAS("of:N*T*Cti,dac124s085");
MODULE_ALIAS("of:N*T*Cti,dac124s085C*");
