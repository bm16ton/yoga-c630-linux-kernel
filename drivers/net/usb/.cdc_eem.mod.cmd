cmd_drivers/net/usb/cdc_eem.mod := printf '%s\n'   cdc_eem.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cdc_eem.mod
