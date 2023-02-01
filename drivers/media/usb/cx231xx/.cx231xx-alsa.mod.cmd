cmd_drivers/media/usb/cx231xx/cx231xx-alsa.mod := printf '%s\n'   cx231xx-audio.o | awk '!x[$$0]++ { print("drivers/media/usb/cx231xx/"$$0) }' > drivers/media/usb/cx231xx/cx231xx-alsa.mod
