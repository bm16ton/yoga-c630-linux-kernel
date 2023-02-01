cmd_drivers/net/usb/cdc_mbim.mod := printf '%s\n'   cdc_mbim.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc_mbim.mod
