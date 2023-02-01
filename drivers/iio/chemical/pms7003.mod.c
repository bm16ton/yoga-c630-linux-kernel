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

MODULE_ALIAS("of:N*T*Cplantower,pms1003");
MODULE_ALIAS("of:N*T*Cplantower,pms1003C*");
MODULE_ALIAS("of:N*T*Cplantower,pms3003");
MODULE_ALIAS("of:N*T*Cplantower,pms3003C*");
MODULE_ALIAS("of:N*T*Cplantower,pms5003");
MODULE_ALIAS("of:N*T*Cplantower,pms5003C*");
MODULE_ALIAS("of:N*T*Cplantower,pms6003");
MODULE_ALIAS("of:N*T*Cplantower,pms6003C*");
MODULE_ALIAS("of:N*T*Cplantower,pms7003");
MODULE_ALIAS("of:N*T*Cplantower,pms7003C*");
MODULE_ALIAS("of:N*T*Cplantower,pmsa003");
MODULE_ALIAS("of:N*T*Cplantower,pmsa003C*");
