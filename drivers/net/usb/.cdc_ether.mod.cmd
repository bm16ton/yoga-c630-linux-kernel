cmd_drivers/net/usb/cdc_ether.mod := printf '%s\n'   cdc_ether.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc_ether.mod
