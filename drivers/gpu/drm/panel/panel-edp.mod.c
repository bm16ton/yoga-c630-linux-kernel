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

MODULE_INFO(depends, "drm_dp_aux_bus,drm,drm_display_helper");

MODULE_ALIAS("of:N*T*Cedp-panel");
MODULE_ALIAS("of:N*T*Cedp-panelC*");
MODULE_ALIAS("of:N*T*Cauo,b101ean01");
MODULE_ALIAS("of:N*T*Cauo,b101ean01C*");
MODULE_ALIAS("of:N*T*Cauo,b116xa01");
MODULE_ALIAS("of:N*T*Cauo,b116xa01C*");
MODULE_ALIAS("of:N*T*Cauo,b116xw03");
MODULE_ALIAS("of:N*T*Cauo,b116xw03C*");
MODULE_ALIAS("of:N*T*Cauo,b133han05");
MODULE_ALIAS("of:N*T*Cauo,b133han05C*");
MODULE_ALIAS("of:N*T*Cauo,b133htn01");
MODULE_ALIAS("of:N*T*Cauo,b133htn01C*");
MODULE_ALIAS("of:N*T*Cauo,b133xtn01");
MODULE_ALIAS("of:N*T*Cauo,b133xtn01C*");
MODULE_ALIAS("of:N*T*Cauo,b140han06");
MODULE_ALIAS("of:N*T*Cauo,b140han06C*");
MODULE_ALIAS("of:N*T*Cboe,nv101wxmn51");
MODULE_ALIAS("of:N*T*Cboe,nv101wxmn51C*");
MODULE_ALIAS("of:N*T*Cboe,nv110wtm-n61");
MODULE_ALIAS("of:N*T*Cboe,nv110wtm-n61C*");
MODULE_ALIAS("of:N*T*Cboe,nv133fhm-n61");
MODULE_ALIAS("of:N*T*Cboe,nv133fhm-n61C*");
MODULE_ALIAS("of:N*T*Cboe,nv133fhm-n62");
MODULE_ALIAS("of:N*T*Cboe,nv133fhm-n62C*");
MODULE_ALIAS("of:N*T*Cboe,nv140fhmn49");
MODULE_ALIAS("of:N*T*Cboe,nv140fhmn49C*");
MODULE_ALIAS("of:N*T*Cinnolux,n116bca-ea1");
MODULE_ALIAS("of:N*T*Cinnolux,n116bca-ea1C*");
MODULE_ALIAS("of:N*T*Cinnolux,n116bge");
MODULE_ALIAS("of:N*T*Cinnolux,n116bgeC*");
MODULE_ALIAS("of:N*T*Cinnolux,n125hce-gn1");
MODULE_ALIAS("of:N*T*Cinnolux,n125hce-gn1C*");
MODULE_ALIAS("of:N*T*Cinnolux,p120zdg-bf1");
MODULE_ALIAS("of:N*T*Cinnolux,p120zdg-bf1C*");
MODULE_ALIAS("of:N*T*Civo,m133nwf4-r0");
MODULE_ALIAS("of:N*T*Civo,m133nwf4-r0C*");
MODULE_ALIAS("of:N*T*Ckingdisplay,kd116n21-30nv-a010");
MODULE_ALIAS("of:N*T*Ckingdisplay,kd116n21-30nv-a010C*");
MODULE_ALIAS("of:N*T*Clg,lp079qx1-sp0v");
MODULE_ALIAS("of:N*T*Clg,lp079qx1-sp0vC*");
MODULE_ALIAS("of:N*T*Clg,lp097qx1-spa1");
MODULE_ALIAS("of:N*T*Clg,lp097qx1-spa1C*");
MODULE_ALIAS("of:N*T*Clg,lp120up1");
MODULE_ALIAS("of:N*T*Clg,lp120up1C*");
MODULE_ALIAS("of:N*T*Clg,lp129qe");
MODULE_ALIAS("of:N*T*Clg,lp129qeC*");
MODULE_ALIAS("of:N*T*Cneweast,wjfh116008a");
MODULE_ALIAS("of:N*T*Cneweast,wjfh116008aC*");
MODULE_ALIAS("of:N*T*Csamsung,lsn122dl01-c01");
MODULE_ALIAS("of:N*T*Csamsung,lsn122dl01-c01C*");
MODULE_ALIAS("of:N*T*Csamsung,ltn140at29-301");
MODULE_ALIAS("of:N*T*Csamsung,ltn140at29-301C*");
MODULE_ALIAS("of:N*T*Csharp,ld-d5116z01b");
MODULE_ALIAS("of:N*T*Csharp,ld-d5116z01bC*");
MODULE_ALIAS("of:N*T*Csharp,lq123p1jx31");
MODULE_ALIAS("of:N*T*Csharp,lq123p1jx31C*");
MODULE_ALIAS("of:N*T*Csharp,lq140m1jw46");
MODULE_ALIAS("of:N*T*Csharp,lq140m1jw46C*");
MODULE_ALIAS("of:N*T*Cstarry,kr122ea0sra");
MODULE_ALIAS("of:N*T*Cstarry,kr122ea0sraC*");
