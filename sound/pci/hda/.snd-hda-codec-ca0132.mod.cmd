cmd_sound/pci/hda/snd-hda-codec-ca0132.mod := printf '%s\n'   patch_ca0132.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-ca0132.mod
