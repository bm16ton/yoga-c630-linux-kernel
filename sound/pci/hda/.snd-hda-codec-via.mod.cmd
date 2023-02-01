cmd_sound/pci/hda/snd-hda-codec-via.mod := printf '%s\n'   patch_via.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-via.mod
