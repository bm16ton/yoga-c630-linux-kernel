cmd_sound/pci/hda/snd-hda-codec-idt.mod := printf '%s\n'   patch_sigmatel.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-idt.mod
