cmd_drivers/usb/misc/usblcd.mod := printf '%s\n'   usblcd.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/usblcd.mod
