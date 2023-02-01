cmd_drivers/net/usb/cdc_subset.mod := printf '%s\n'   cdc_subset.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc_subset.mod
