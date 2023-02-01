cmd_sound/pci/riptide/snd-riptide.mod := printf '%s\n'   riptide.o | awk '!x[$$0]++ { print("sound/pci/riptide/"$$0) }' > sound/pci/riptide/snd-riptide.mod
