cmd_drivers/net/wireless/atmel/at76c50x-usb.mod := printf '%s\n'   at76c50x-usb.o | awk '!x[$$0]++ { print("drivers/net/wireless/atmel/"$$0) }' > drivers/net/wireless/atmel/at76c50x-usb.mod
