cmd_drivers/usb/atm/xusbatm.mod := printf '%s\n'   xusbatm.o | awk '!x[$$0]++ { print("drivers/usb/atm/"$$0) }' > drivers/usb/atm/xusbatm.mod
