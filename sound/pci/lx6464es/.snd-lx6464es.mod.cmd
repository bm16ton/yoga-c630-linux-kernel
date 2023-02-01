cmd_sound/pci/lx6464es/snd-lx6464es.mod := printf '%s\n'   lx6464es.o lx_core.o | awk '!x[$$0]++ { print("sound/pci/lx6464es/"$$0) }' > sound/pci/lx6464es/snd-lx6464es.mod
