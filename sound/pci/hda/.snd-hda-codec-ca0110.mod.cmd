cmd_sound/pci/hda/snd-hda-codec-ca0110.mod := printf '%s\n'   patch_ca0110.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-ca0110.mod
