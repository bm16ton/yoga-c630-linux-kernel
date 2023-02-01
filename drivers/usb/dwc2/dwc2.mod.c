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

MODULE_INFO(depends, "udc-core");

MODULE_ALIAS("acpi*:BCM2848:*");
MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-usb");
MODULE_ALIAS("of:N*T*Cbrcm,bcm2835-usbC*");
MODULE_ALIAS("of:N*T*Chisilicon,hi6220-usb");
MODULE_ALIAS("of:N*T*Chisilicon,hi6220-usbC*");
MODULE_ALIAS("of:N*T*Cingenic,jz4775-otg");
MODULE_ALIAS("of:N*T*Cingenic,jz4775-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,jz4780-otg");
MODULE_ALIAS("of:N*T*Cingenic,jz4780-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,x1000-otg");
MODULE_ALIAS("of:N*T*Cingenic,x1000-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,x1600-otg");
MODULE_ALIAS("of:N*T*Cingenic,x1600-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,x1700-otg");
MODULE_ALIAS("of:N*T*Cingenic,x1700-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,x1830-otg");
MODULE_ALIAS("of:N*T*Cingenic,x1830-otgC*");
MODULE_ALIAS("of:N*T*Cingenic,x2000-otg");
MODULE_ALIAS("of:N*T*Cingenic,x2000-otgC*");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-usb");
MODULE_ALIAS("of:N*T*Crockchip,rk3066-usbC*");
MODULE_ALIAS("of:N*T*Clantiq,arx100-usb");
MODULE_ALIAS("of:N*T*Clantiq,arx100-usbC*");
MODULE_ALIAS("of:N*T*Clantiq,xrx200-usb");
MODULE_ALIAS("of:N*T*Clantiq,xrx200-usbC*");
MODULE_ALIAS("of:N*T*Csnps,dwc2");
MODULE_ALIAS("of:N*T*Csnps,dwc2C*");
MODULE_ALIAS("of:N*T*Csamsung,s3c6400-hsotg");
MODULE_ALIAS("of:N*T*Csamsung,s3c6400-hsotgC*");
MODULE_ALIAS("of:N*T*Camlogic,meson8-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson8-usbC*");
MODULE_ALIAS("of:N*T*Camlogic,meson8b-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson8b-usbC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson-gxbb-usbC*");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-usb");
MODULE_ALIAS("of:N*T*Camlogic,meson-g12a-usbC*");
MODULE_ALIAS("of:N*T*Camcc,dwc-otg");
MODULE_ALIAS("of:N*T*Camcc,dwc-otgC*");
MODULE_ALIAS("of:N*T*Capm,apm82181-dwc-otg");
MODULE_ALIAS("of:N*T*Capm,apm82181-dwc-otgC*");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-fsotg");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-fsotgC*");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-hsotg");
MODULE_ALIAS("of:N*T*Cst,stm32f4x9-hsotgC*");
MODULE_ALIAS("of:N*T*Cst,stm32f7-hsotg");
MODULE_ALIAS("of:N*T*Cst,stm32f7-hsotgC*");
MODULE_ALIAS("of:N*T*Cst,stm32mp15-fsotg");
MODULE_ALIAS("of:N*T*Cst,stm32mp15-fsotgC*");
MODULE_ALIAS("of:N*T*Cst,stm32mp15-hsotg");
MODULE_ALIAS("of:N*T*Cst,stm32mp15-hsotgC*");
MODULE_ALIAS("of:N*T*Cintel,socfpga-agilex-hsotg");
MODULE_ALIAS("of:N*T*Cintel,socfpga-agilex-hsotgC*");
