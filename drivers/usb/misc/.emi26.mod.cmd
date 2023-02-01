cmd_drivers/usb/misc/emi26.mod := printf '%s\n'   emi26.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/emi26.mod
