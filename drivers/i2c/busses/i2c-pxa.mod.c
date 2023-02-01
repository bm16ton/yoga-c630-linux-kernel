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

MODULE_ALIAS("platform:pxa2xx-i2c");
MODULE_ALIAS("platform:pxa3xx-pwri2c");
MODULE_ALIAS("platform:ce4100-i2c");
MODULE_ALIAS("platform:pxa910-i2c");
MODULE_ALIAS("platform:armada-3700-i2c");
MODULE_ALIAS("of:N*T*Cmrvl,pxa-i2c");
MODULE_ALIAS("of:N*T*Cmrvl,pxa-i2cC*");
MODULE_ALIAS("of:N*T*Cmrvl,pwri2c");
MODULE_ALIAS("of:N*T*Cmrvl,pwri2cC*");
MODULE_ALIAS("of:N*T*Cmrvl,mmp-twsi");
MODULE_ALIAS("of:N*T*Cmrvl,mmp-twsiC*");
MODULE_ALIAS("of:N*T*Cmarvell,armada-3700-i2c");
MODULE_ALIAS("of:N*T*Cmarvell,armada-3700-i2cC*");
