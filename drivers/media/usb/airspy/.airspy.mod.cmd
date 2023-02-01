cmd_drivers/media/usb/airspy/airspy.mod := printf '%s\n'   airspy.o | awk '!x[$$0]++ { print("drivers/media/usb/airspy/"$$0) }' > drivers/media/usb/airspy/airspy.mod
