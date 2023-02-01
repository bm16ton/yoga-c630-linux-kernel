cmd_sound/pci/hda/snd-hda-codec-realtek.mod := printf '%s\n'   patch_realtek.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-realtek.mod
