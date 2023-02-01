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

MODULE_INFO(depends, "firewire-core,snd-firewire-lib,snd-pcm,snd,snd-hwdep,snd-rawmidi");

MODULE_ALIAS("ieee1394:ven00000FF2mo0000400Fsp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00000FF2mo0001200Fsp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo00000AF8sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo0000AF12sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo000AF12Dsp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo000AF12Asp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo00000AF2sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo00000AF4sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo00000AF9sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo000000F8sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven00001486mo0000AFD1sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven0000075Bmo0000AFB2sp0000A02Dver00010000*");
MODULE_ALIAS("ieee1394:ven0000075Bmo0000AFB9sp0000A02Dver00010000*");
