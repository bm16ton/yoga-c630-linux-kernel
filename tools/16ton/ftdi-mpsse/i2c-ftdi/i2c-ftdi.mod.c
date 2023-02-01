#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf3bb3eea, "module_layout" },
	{ 0x1f635005, "param_ops_int" },
	{ 0x10c09b86, "usb_deregister" },
	{ 0xb819053c, "usb_register_driver" },
	{ 0x1f9f16ba, "i2c_add_adapter" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x4db0f56c, "_dev_err" },
	{ 0xbbe80fdb, "kmalloc_order" },
	{ 0x8e13ede, "device_create_file" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x92382b70, "usb_get_intf" },
	{ 0x73c5ef8d, "usb_get_dev" },
	{ 0xb0b1a325, "kmem_cache_alloc" },
	{ 0xdd7fb546, "kmalloc_caches" },
	{ 0x12a38747, "usleep_range" },
	{ 0x6792ddf7, "usb_control_msg" },
	{ 0x4829a47e, "memcpy" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xf706e2ef, "usb_bulk_msg" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x6c432ee8, "i2c_del_adapter" },
	{ 0x1cf7fe20, "device_remove_file" },
	{ 0x37a0cba, "kfree" },
	{ 0x7e69e00f, "usb_put_dev" },
	{ 0x996759bf, "usb_put_intf" },
	{ 0x96848186, "scnprintf" },
	{ 0x66762163, "_dev_info" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("usb:v0403p6011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0403p6041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0403p6010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0403p6014d*dc*dsc*dp*ic*isc*ip*in*");
