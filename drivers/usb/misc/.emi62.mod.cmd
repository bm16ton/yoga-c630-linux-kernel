cmd_drivers/usb/misc/emi62.mod := printf '%s\n'   emi62.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/emi62.mod
