cmd_drivers/media/usb/em28xx/em28xx-alsa.mod := printf '%s\n'   em28xx-audio.o | awk '!x[$$0]++ { print("drivers/media/usb/em28xx/"$$0) }' > drivers/media/usb/em28xx/em28xx-alsa.mod
