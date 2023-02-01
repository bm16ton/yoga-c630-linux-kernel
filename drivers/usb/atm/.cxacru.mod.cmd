cmd_drivers/usb/atm/cxacru.mod := printf '%s\n'   cxacru.o | awk '!x[$$0]++ { print("drivers/usb/atm/"$$0) }' > drivers/usb/atm/cxacru.mod
