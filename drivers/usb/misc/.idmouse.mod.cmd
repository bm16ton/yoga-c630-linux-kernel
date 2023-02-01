cmd_drivers/usb/misc/idmouse.mod := printf '%s\n'   idmouse.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/idmouse.mod
