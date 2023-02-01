cmd_sound/pci/hda/snd-hda-codec-analog.mod := printf '%s\n'   patch_analog.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-analog.mod
