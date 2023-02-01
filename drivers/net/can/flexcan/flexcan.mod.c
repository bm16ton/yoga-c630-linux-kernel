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

MODULE_INFO(depends, "can-dev");

MODULE_ALIAS("platform:flexcan-mcf5441x");
MODULE_ALIAS("of:N*T*Cfsl,imx8qm-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx8qm-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx8mp-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx8mp-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx28-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx28-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx53-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx53-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx35-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx35-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,imx25-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx25-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,p1010-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,p1010-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,vf610-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,vf610-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,ls1021ar2-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,ls1021ar2-flexcanC*");
MODULE_ALIAS("of:N*T*Cfsl,lx2160ar1-flexcan");
MODULE_ALIAS("of:N*T*Cfsl,lx2160ar1-flexcanC*");
