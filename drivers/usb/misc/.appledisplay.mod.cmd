cmd_drivers/usb/misc/appledisplay.mod := printf '%s\n'   appledisplay.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/appledisplay.mod
