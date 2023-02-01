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

MODULE_INFO(depends, "mac80211,cfg80211");

MODULE_ALIAS("usb:v0BDAp8724d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp1724d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp0724d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp818Bd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2357p0108d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p3319d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2357p0109d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDApB720d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v7392pA611d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp8176d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp8178d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp817Fd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v7392p7811d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v050Dp1004d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v20F4p648Bd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p3308d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp018Ad*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp8191d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp8170d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp8177d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp817Ad*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp817Bd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp817Dd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp817Ed*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp818Ad*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp317Fd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v1058p0631d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04BBp094Cd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v050Dp1102d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v06F8pE033d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v07B8p8189d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0846p9041d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0B05p17BAd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp1E1Ed*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp5088d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0DF6p0052d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0DF6p005Cd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0EB0p9071d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v103Cp1629d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v13D3p3357d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p330Bd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019p4902d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019pAB2Ad*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019pAB2Ed*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019pED17d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v4855p0090d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v4856p0091d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:vCDABp8010d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFF7d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFF9d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFFAd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFF8d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFFBd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04F2pAFFCd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019p1201d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v04BBp0950d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v050Dp2102d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v050Dp2103d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0586p341Fd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v06F8pE035d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0B05p17ABd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0DF6p0061d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0DF6p0070d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0789p016Dd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v07AAp0056d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v07B8p8178d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0846p9021d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0846pF001d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp2E2Ed*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0E66p0019d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0E66p0020d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p3307d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p3309d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2001p330Ad*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019pAB2Bd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v20F4p624Dd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2357p0100d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v4855p0091d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v7392p7822d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2357p0107d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v2019pAB33d*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v0BDAp818Cd*dc*dsc*dp*icFFiscFFipFFin*");
