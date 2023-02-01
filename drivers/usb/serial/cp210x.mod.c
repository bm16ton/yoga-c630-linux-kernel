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

MODULE_ALIAS("usb:v0404p034Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v045Bp0053d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p066Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0489pE000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0489pE003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0745p1000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p1100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08E6p5501d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08FDp000Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0908p0070d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0908p01FFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0988p0578d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B00p3070d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BEDp1100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BEDp1101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FCFp1003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FCFp1004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FCFp1006d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FDEpCA05d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v106Fp0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10A6pAA26d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10ABp10C5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B5pAC70d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p0F91d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p1101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p1601d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p800Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p803Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8044d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p804Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8053d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8054d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8056d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8066d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p806Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p807Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p80C4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p80CAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p80DDd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p80F6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8115d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p813Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p813Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p814Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p814Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2405p0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8156d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p815Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p815Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p817Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p817Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p817Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p818Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p819Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81A6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81A9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81ACd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81ADd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81C8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81D7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81E2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81E7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81E8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p81F2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8218d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p822Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p826Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8281d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8293d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p82EFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p82F1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p82F2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p82F4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p82F9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8341d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8382d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p83A8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p83AAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p83D8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8411d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8414d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8418d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p846Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8470d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8477d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p84B6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p851Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p85A7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p85B8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p85EAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p85EBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p85F8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8664d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8665d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8856d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8857d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p88A4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p88A5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p88D8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p88FBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8938d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8946d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8962d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8977d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8998d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p89A4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p89FBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8A2Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8A5Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8A5Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4p8B34d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA60d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA61d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA63d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA70d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA71d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA7Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pEA7Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pF001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pF002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pF003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C4pF004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10C5pEA61d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10CEpEA6Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v12B8pEC60d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v12B8pEC62d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13ADp9999d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1555p0004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v155Ap1006d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0201d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0303d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0304d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0305d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0401d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v166Ap0101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16C0p09B0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16C0p09B1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16D6p0001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16DCp0010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16DCp0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16DCp0012d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v16DCp0015d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17A8p0001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17A8p0005d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17A8p0101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17A8p0102d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17F4pAAAAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1843p0200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18EFpE00Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18EFpE025d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18EFpE030d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18EFpE032d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0190d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0193d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0194d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0195d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0196d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0197d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1901p0198d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v199BpBA30d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19CFp3000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1ADBp0001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B1Cp1C00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1BA4p0002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1BE3p07A6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1D6Fp0010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1E29p0102d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1E29p0501d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0201d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0202d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0203d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0300d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0302d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0303d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0400d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0401d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0402d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0403d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0404d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0600d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0601d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0602d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0700d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1FB9p0701d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2184p0030d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2626pEA60d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v3195pF190d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v3195pF280d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v3195pF281d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v3923p7A0Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v413Cp9500d*dc*dsc*dp*ic*isc*ip*in*");
