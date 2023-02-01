cmd_drivers/media/cec/usb/pulse8/pulse8-cec.mod := printf '%s\n'   pulse8-cec.o | awk '!x[$$0]++ { print("drivers/media/cec/usb/pulse8/"$$0) }' > drivers/media/cec/usb/pulse8/pulse8-cec.mod
