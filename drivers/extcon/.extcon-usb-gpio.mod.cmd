cmd_drivers/extcon/extcon-usb-gpio.mod := printf '%s\n'   extcon-usb-gpio.o | awk '!x[$$0]++ { print("drivers/extcon/"$$0) }' > drivers/extcon/extcon-usb-gpio.mod
