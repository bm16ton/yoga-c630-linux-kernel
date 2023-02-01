# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
ccflags-y := -I$(srctree)/arch/arm/plat-orion/include
=======
ccflags-$(CONFIG_ARCH_MULTIPLATFORM) := -I$(srctree)/arch/arm/plat-orion/include
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

obj-y				+= common.o
obj-$(CONFIG_DOVE_LEGACY)	+= irq.o mpp.o
obj-$(CONFIG_PCI)		+= pcie.o
obj-$(CONFIG_MACH_DOVE_DB)	+= dove-db-setup.o
obj-$(CONFIG_MACH_CM_A510)	+= cm-a510.o
