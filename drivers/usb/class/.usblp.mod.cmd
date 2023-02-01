cmd_drivers/usb/class/usblp.mod := printf '%s\n'   usblp.o | awk '!x[$$0]++ { print("drivers/usb/class/"$$0) }' > drivers/usb/class/usblp.mod
