cmd_drivers/usb/misc/iowarrior.mod := printf '%s\n'   iowarrior.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/iowarrior.mod
