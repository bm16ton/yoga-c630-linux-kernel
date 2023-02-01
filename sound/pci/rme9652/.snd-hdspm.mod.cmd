cmd_sound/pci/rme9652/snd-hdspm.mod := printf '%s\n'   hdspm.o | awk '!x[$$0]++ { print("sound/pci/rme9652/"$$0) }' > sound/pci/rme9652/snd-hdspm.mod
