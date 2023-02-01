cmd_drivers/media/pci/cx18/cx18-alsa.mod := printf '%s\n'   cx18-alsa-main.o cx18-alsa-pcm.o | awk '!x[$$0]++ { print("drivers/media/pci/cx18/"$$0) }' > drivers/media/pci/cx18/cx18-alsa.mod
