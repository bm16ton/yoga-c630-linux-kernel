cmd_drivers/usb/misc/onboard_usb_hub.mod := printf '%s\n'   onboard_usb_hub.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/onboard_usb_hub.mod
