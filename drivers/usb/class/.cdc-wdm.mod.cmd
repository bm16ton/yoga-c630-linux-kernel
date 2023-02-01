cmd_drivers/usb/class/cdc-wdm.mod := printf '%s\n'   cdc-wdm.o | awk '!x[$$0]++ { print("drivers/usb/class/"$$0) }' > drivers/usb/class/cdc-wdm.mod
