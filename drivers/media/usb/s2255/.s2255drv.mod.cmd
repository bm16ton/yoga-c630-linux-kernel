cmd_drivers/media/usb/s2255/s2255drv.mod := printf '%s\n'   s2255drv.o | awk '!x[$$0]++ { print("drivers/media/usb/s2255/"$$0) }' > drivers/media/usb/s2255/s2255drv.mod
