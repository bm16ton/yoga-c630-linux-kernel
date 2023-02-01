cmd_sound/pci/hda/snd-hda-codec-si3054.mod := printf '%s\n'   patch_si3054.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-si3054.mod
