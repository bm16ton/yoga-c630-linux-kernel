cmd_drivers/usb/serial/kobil_sct.mod := printf '%s\n'   kobil_sct.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/kobil_sct.mod
