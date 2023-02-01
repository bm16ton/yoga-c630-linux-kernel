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

MODULE_INFO(depends, "firewire-core,snd-firewire-lib,snd-rawmidi,snd,snd-pcm,snd-hwdep");

MODULE_ALIAS("ieee1394:ven00001292mo0000F970sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven0000D04Bmo0000F970sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00001564mo0000FC22sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00000FF2mo00000460sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00000FF2mo0000200Fsp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00000FF2mo*sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven0000022Emo00800007sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00001260mo00001000sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven00001260mo00002000sp0000A02Dver00010001*");
MODULE_ALIAS("ieee1394:ven000003DBmo0001DDDDsp0000A02Dver00010001*");
