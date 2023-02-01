cmd_drivers/power/supply/axp20x_usb_power.mod := printf '%s\n'   axp20x_usb_power.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/axp20x_usb_power.mod
