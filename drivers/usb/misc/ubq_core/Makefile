# SPDX-License-Identifier: GPL-2.0
#
# USB Miscellaneous driver configuration
#
#comment "USB usbq drivers"
#ccflags-y+=-Wfatal-errors
#ccflags-y+=-include $M/ctracer.h
#ccflags-y+=-D CTRACER_ON

obj-m += ubq_core.o
EXTRA_CFLAGS += -g -fms-extensions

ubq_core-y := core.o gadget.o driver.o com.o com_udp.o debug.o debug_usb.o common.o msg.o




