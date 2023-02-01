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

MODULE_INFO(depends, "usbmisc_imx,ci_hdrc");

MODULE_ALIAS("of:N*T*Cfsl,imx23-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx23-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx28-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx28-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx27-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx27-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6sl-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx6sl-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6sx-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx6sx-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx6ul-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx6ul-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx7d-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx7d-usbC*");
MODULE_ALIAS("of:N*T*Cfsl,imx7ulp-usb");
MODULE_ALIAS("of:N*T*Cfsl,imx7ulp-usbC*");
