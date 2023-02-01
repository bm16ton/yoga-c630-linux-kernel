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

MODULE_ALIAS("pci:v0000494Fd00001052sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd0000105Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd0000106Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd000010A8sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd000010D2sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd000010DBsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000494Fd000010EAsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv000012C4sd00000300bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000154sv000012C4sd00000301bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000158sv000012C4sd00000302bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv000012C4sd00000310bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000154sv000012C4sd00000311bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000158sv000012C4sd00000312bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv000012C4sd00000320bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000154sv000012C4sd00000321bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000158sv000012C4sd00000322bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv000012C4sd00000330bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000154sv000012C4sd00000331bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000158sv000012C4sd00000332bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv00001014sd000003D4bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000152sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000154sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000158sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000352sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000354sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00000358sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00004358sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000013A8d00008358sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d00000022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d00000020sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d00000021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d00000004sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d00000002sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d0000000Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000018F7d0000000Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000135Ed00001001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000135Ed00001002sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000135Ed00001004sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000135Ed00001008sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000135Ed00001010sv*sd*bc*sc*i*");
