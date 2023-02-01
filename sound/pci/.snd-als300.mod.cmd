cmd_sound/pci/snd-als300.mod := printf '%s\n'   als300.o | awk '!x[$$0]++ { print("sound/pci/"$$0) }' > sound/pci/snd-als300.mod
