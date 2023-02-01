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

MODULE_INFO(depends, "firewire-core,snd-rawmidi,snd-firewire-lib,snd-pcm,snd,snd-hwdep");

MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000001*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000002*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000003*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000005*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000009*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver0000000D*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver0000000F*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000015*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000019*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver0000001B*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000030*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000035*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000033*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000039*");
MODULE_ALIAS("ieee1394:ven000001F2mo*sp000001F2ver00000045*");
