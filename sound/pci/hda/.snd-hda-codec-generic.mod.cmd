cmd_sound/pci/hda/snd-hda-codec-generic.mod := printf '%s\n'   hda_generic.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-generic.mod
