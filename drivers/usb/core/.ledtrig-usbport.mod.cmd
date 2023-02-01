cmd_drivers/usb/core/ledtrig-usbport.mod := printf '%s\n'   ledtrig-usbport.o | awk '!x[$$0]++ { print("drivers/usb/core/"$$0) }' > drivers/usb/core/ledtrig-usbport.mod
