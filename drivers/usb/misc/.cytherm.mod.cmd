cmd_drivers/usb/misc/cytherm.mod := printf '%s\n'   cytherm.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/cytherm.mod
