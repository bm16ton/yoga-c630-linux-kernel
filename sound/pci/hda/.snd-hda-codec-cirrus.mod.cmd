cmd_sound/pci/hda/snd-hda-codec-cirrus.mod := printf '%s\n'   patch_cirrus.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-cirrus.mod
