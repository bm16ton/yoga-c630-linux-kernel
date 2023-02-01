cmd_drivers/usb/misc/legousbtower.mod := printf '%s\n'   legousbtower.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/legousbtower.mod
