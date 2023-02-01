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

MODULE_ALIAS("of:N*T*Celan,ekth3000");
MODULE_ALIAS("of:N*T*Celan,ekth3000C*");
MODULE_ALIAS("acpi*:ELAN0000:*");
MODULE_ALIAS("acpi*:ELAN0100:*");
MODULE_ALIAS("acpi*:ELAN0600:*");
MODULE_ALIAS("acpi*:ELAN0601:*");
MODULE_ALIAS("acpi*:ELAN0602:*");
MODULE_ALIAS("acpi*:ELAN0603:*");
MODULE_ALIAS("acpi*:ELAN0604:*");
MODULE_ALIAS("acpi*:ELAN0605:*");
MODULE_ALIAS("acpi*:ELAN0606:*");
MODULE_ALIAS("acpi*:ELAN0607:*");
MODULE_ALIAS("acpi*:ELAN0608:*");
MODULE_ALIAS("acpi*:ELAN0609:*");
MODULE_ALIAS("acpi*:ELAN060B:*");
MODULE_ALIAS("acpi*:ELAN060C:*");
MODULE_ALIAS("acpi*:ELAN060F:*");
MODULE_ALIAS("acpi*:ELAN0610:*");
MODULE_ALIAS("acpi*:ELAN0611:*");
MODULE_ALIAS("acpi*:ELAN0612:*");
MODULE_ALIAS("acpi*:ELAN0615:*");
MODULE_ALIAS("acpi*:ELAN0616:*");
MODULE_ALIAS("acpi*:ELAN0617:*");
MODULE_ALIAS("acpi*:ELAN0618:*");
MODULE_ALIAS("acpi*:ELAN0619:*");
MODULE_ALIAS("acpi*:ELAN061A:*");
MODULE_ALIAS("acpi*:ELAN061C:*");
MODULE_ALIAS("acpi*:ELAN061D:*");
MODULE_ALIAS("acpi*:ELAN061E:*");
MODULE_ALIAS("acpi*:ELAN061F:*");
MODULE_ALIAS("acpi*:ELAN0620:*");
MODULE_ALIAS("acpi*:ELAN0621:*");
MODULE_ALIAS("acpi*:ELAN0622:*");
MODULE_ALIAS("acpi*:ELAN0623:*");
MODULE_ALIAS("acpi*:ELAN0624:*");
MODULE_ALIAS("acpi*:ELAN0625:*");
MODULE_ALIAS("acpi*:ELAN0626:*");
MODULE_ALIAS("acpi*:ELAN0627:*");
MODULE_ALIAS("acpi*:ELAN0628:*");
MODULE_ALIAS("acpi*:ELAN0629:*");
MODULE_ALIAS("acpi*:ELAN062A:*");
MODULE_ALIAS("acpi*:ELAN062B:*");
MODULE_ALIAS("acpi*:ELAN062C:*");
MODULE_ALIAS("acpi*:ELAN062D:*");
MODULE_ALIAS("acpi*:ELAN062E:*");
MODULE_ALIAS("acpi*:ELAN062F:*");
MODULE_ALIAS("acpi*:ELAN0631:*");
MODULE_ALIAS("acpi*:ELAN0632:*");
MODULE_ALIAS("acpi*:ELAN0633:*");
MODULE_ALIAS("acpi*:ELAN0634:*");
MODULE_ALIAS("acpi*:ELAN0635:*");
MODULE_ALIAS("acpi*:ELAN0636:*");
MODULE_ALIAS("acpi*:ELAN0637:*");
MODULE_ALIAS("acpi*:ELAN1000:*");
MODULE_ALIAS("i2c:elan_i2c");
