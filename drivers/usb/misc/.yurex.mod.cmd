cmd_drivers/usb/misc/yurex.mod := printf '%s\n'   yurex.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/yurex.mod
