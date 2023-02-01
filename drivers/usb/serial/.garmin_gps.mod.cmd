cmd_drivers/usb/serial/garmin_gps.mod := printf '%s\n'   garmin_gps.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/garmin_gps.mod
