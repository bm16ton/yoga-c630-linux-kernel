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

MODULE_INFO(depends, "mc,videodev,tveeprom");

MODULE_ALIAS("usb:vEB1Ap2750d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2751d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2800d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2710d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2820d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2821d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2860d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2861d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2862d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2863d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2870d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2881d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2883d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2868d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2875d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2885d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE300d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE303d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE305d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE310d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApA313d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApA316d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE320d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE323d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE350d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE355d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap2801d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE357d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1ApE359d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE302d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE304d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0036d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp004Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp004Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp005Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0042d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0043d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp008Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp00ACd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10A2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10ADd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10B6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10B2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0084d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0096d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10AFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp00B2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p0018d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p0033d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v185Bp2870d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v185Bp2041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p4200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p4201d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p6500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p6502d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p6513d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p6517d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p651Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p651Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p0265d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p8265d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p026Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p826Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p846Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0438pB002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001pF112d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0207d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0208d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p021Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0226d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0227d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p023Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0413p6023d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v093BpA003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v093BpA005d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04BBp0515d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap50A6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pA340d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE346d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE34Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p024Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p024Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p1605d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE755d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap5006d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE309d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE425d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1F4Dp1ABEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0242d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0251d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE1CCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1AE7p9003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1AE7p9004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0258d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p8258d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0461d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p8461d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0259d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p025Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0264d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p0264d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p8264d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p8268d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0413p6F07d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap8179d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v3275p0085d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:vEB1Ap5051d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B80pE349d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "020A767F5641624CC2827CD");
