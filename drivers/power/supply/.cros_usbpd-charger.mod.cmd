cmd_drivers/power/supply/cros_usbpd-charger.mod := printf '%s\n'   cros_usbpd-charger.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/cros_usbpd-charger.mod
