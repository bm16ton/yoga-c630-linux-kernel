cmd_drivers/usb/misc/uss720.mod := printf '%s\n'   uss720.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/uss720.mod
