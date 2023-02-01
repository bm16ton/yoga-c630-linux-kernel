cmd_drivers/net/usb/cdc_ncm.mod := printf '%s\n'   cdc_ncm.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc_ncm.mod
