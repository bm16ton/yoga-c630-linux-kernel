cmd_drivers/usb/class/usbtmc.mod := printf '%s\n'   usbtmc.o | awk '!x[$$0]++ { print("drivers/usb/class/"$$0) }' > drivers/usb/class/usbtmc.mod
