cmd_drivers/usb/serial/belkin_sa.mod := printf '%s\n'   belkin_sa.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/belkin_sa.mod
