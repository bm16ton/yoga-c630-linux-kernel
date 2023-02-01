cmd_sound/pci/hda/snd-hda-intel.mod := printf '%s\n'   hda_intel.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-intel.mod
