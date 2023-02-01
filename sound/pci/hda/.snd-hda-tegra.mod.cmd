cmd_sound/pci/hda/snd-hda-tegra.mod := printf '%s\n'   hda_tegra.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-tegra.mod
