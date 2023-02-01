cmd_drivers/media/usb/hackrf/hackrf.mod := printf '%s\n'   hackrf.o | awk '!x[$$0]++ { print("drivers/media/usb/hackrf/"$$0) }' > drivers/media/usb/hackrf/hackrf.mod
