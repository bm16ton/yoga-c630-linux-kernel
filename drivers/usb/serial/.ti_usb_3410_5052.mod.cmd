cmd_drivers/usb/serial/ti_usb_3410_5052.mod := printf '%s\n'   ti_usb_3410_5052.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/ti_usb_3410_5052.mod
