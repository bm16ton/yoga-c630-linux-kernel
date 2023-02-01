cmd_drivers/media/pci/ivtv/ivtv-alsa.mod := printf '%s\n'   ivtv-alsa-main.o ivtv-alsa-pcm.o | awk '!x[$$0]++ { print("drivers/media/pci/ivtv/"$$0) }' > drivers/media/pci/ivtv/ivtv-alsa.mod
