cmd_drivers/usb/misc/apple-mfi-fastcharge.mod := printf '%s\n'   apple-mfi-fastcharge.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/apple-mfi-fastcharge.mod
