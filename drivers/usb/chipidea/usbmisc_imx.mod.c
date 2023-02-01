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

MODULE_ALIAS("of:N*T*Cfsl,imx25-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx25-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx35-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx35-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx27-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx27-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx51-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx51-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx53-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx53-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,vf610-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,vf610-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6sx-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx6sx-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6ul-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx6ul-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx7d-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx7d-usbmiscC*");
MODULE_ALIAS("of:N*T*Cfsl,imx7ulp-usbmisc");
MODULE_ALIAS("of:N*T*Cfsl,imx7ulp-usbmiscC*");
