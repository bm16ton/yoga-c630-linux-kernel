cmd_sound/pci/hda/snd-hda-codec-conexant.mod := printf '%s\n'   patch_conexant.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-conexant.mod
