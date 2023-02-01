cmd_sound/pci/snd-ad1889.mod := printf '%s\n'   ad1889.o | awk '!x[$$0]++ { print("sound/pci/"$$0) }' > sound/pci/snd-ad1889.mod
