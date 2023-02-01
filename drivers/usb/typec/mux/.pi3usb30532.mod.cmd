cmd_drivers/usb/typec/mux/pi3usb30532.mod := printf '%s\n'   pi3usb30532.o | awk '!x[$$0]++ { print("drivers/usb/typec/mux/"$$0) }' > drivers/usb/typec/mux/pi3usb30532.mod
