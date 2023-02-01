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

MODULE_INFO(depends, "industrialio");

MODULE_ALIAS("i2c:abp060mg");
MODULE_ALIAS("i2c:abp006kg");
MODULE_ALIAS("i2c:abp100mg");
MODULE_ALIAS("i2c:abp010kg");
MODULE_ALIAS("i2c:abp160mg");
MODULE_ALIAS("i2c:abp016kg");
MODULE_ALIAS("i2c:abp250mg");
MODULE_ALIAS("i2c:abp025kg");
MODULE_ALIAS("i2c:abp400mg");
MODULE_ALIAS("i2c:abp040kg");
MODULE_ALIAS("i2c:abp600mg");
MODULE_ALIAS("i2c:abp060kg");
MODULE_ALIAS("i2c:abp001bg");
MODULE_ALIAS("i2c:abp100kg");
MODULE_ALIAS("i2c:abp1_6bg");
MODULE_ALIAS("i2c:abp160kg");
MODULE_ALIAS("i2c:abp2_5bg");
MODULE_ALIAS("i2c:abp250kg");
MODULE_ALIAS("i2c:abp004bg");
MODULE_ALIAS("i2c:abp400kg");
MODULE_ALIAS("i2c:abp006bg");
MODULE_ALIAS("i2c:abp600kg");
MODULE_ALIAS("i2c:abp010bg");
MODULE_ALIAS("i2c:abp001gg");
MODULE_ALIAS("i2c:abp060md");
MODULE_ALIAS("i2c:abp006kd");
MODULE_ALIAS("i2c:abp100md");
MODULE_ALIAS("i2c:abp010kd");
MODULE_ALIAS("i2c:abp160md");
MODULE_ALIAS("i2c:abp016kd");
MODULE_ALIAS("i2c:abp250md");
MODULE_ALIAS("i2c:abp025kd");
MODULE_ALIAS("i2c:abp400md");
MODULE_ALIAS("i2c:abp040kd");
MODULE_ALIAS("i2c:abp600md");
MODULE_ALIAS("i2c:abp060kd");
MODULE_ALIAS("i2c:abp001bd");
MODULE_ALIAS("i2c:abp100kd");
MODULE_ALIAS("i2c:abp1_6bd");
MODULE_ALIAS("i2c:abp160kd");
MODULE_ALIAS("i2c:abp2_5bd");
MODULE_ALIAS("i2c:abp250kd");
MODULE_ALIAS("i2c:abp004bd");
MODULE_ALIAS("i2c:abp400kd");
MODULE_ALIAS("i2c:abp001pg");
MODULE_ALIAS("i2c:abp005pg");
MODULE_ALIAS("i2c:abp015pg");
MODULE_ALIAS("i2c:abp030pg");
MODULE_ALIAS("i2c:abp060pg");
MODULE_ALIAS("i2c:abp100pg");
MODULE_ALIAS("i2c:abp150pg");
MODULE_ALIAS("i2c:abp001pd");
MODULE_ALIAS("i2c:abp005pd");
MODULE_ALIAS("i2c:abp015pd");
MODULE_ALIAS("i2c:abp030pd");
MODULE_ALIAS("i2c:abp060pd");
