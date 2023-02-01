cmd_drivers/media/pci/cx88/cx88-alsa.mod := printf '%s\n'   cx88-alsa.o | awk '!x[$$0]++ { print("drivers/media/pci/cx88/"$$0) }' > drivers/media/pci/cx88/cx88-alsa.mod
