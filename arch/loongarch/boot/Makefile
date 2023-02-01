#
# arch/loongarch/boot/Makefile
#
# Copyright (C) 2020-2022 Loongson Technology Corporation Limited
#

drop-sections := .comment .note .options .note.gnu.build-id
strip-flags   := $(addprefix --remove-section=,$(drop-sections)) -S
OBJCOPYFLAGS_vmlinux.efi := -O binary $(strip-flags)

<<<<<<< HEAD
quiet_cmd_strip = STRIP	  $@
      cmd_strip = $(STRIP) -s -o $@ $<

targets := vmlinux.elf
$(obj)/vmlinux.elf: vmlinux FORCE
	$(call if_changed,strip)

targets += vmlinux.efi
$(obj)/vmlinux.efi: vmlinux FORCE
	$(call if_changed,objcopy)

EFI_ZBOOT_PAYLOAD      := vmlinux.efi
EFI_ZBOOT_BFD_TARGET   := elf64-loongarch
EFI_ZBOOT_MACH_TYPE    := LOONGARCH64

include $(srctree)/drivers/firmware/efi/libstub/Makefile.zboot
=======
targets := vmlinux
quiet_cmd_strip = STRIP	  $@
      cmd_strip = $(STRIP) -s -o $@ $<

$(obj)/vmlinux: vmlinux FORCE
	$(call if_changed,strip)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
