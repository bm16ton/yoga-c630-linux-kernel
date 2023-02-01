cmd_drivers/net/usb/cdc-phonet.mod := printf '%s\n'   cdc-phonet.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc-phonet.mod
