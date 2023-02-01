cmd_drivers/usb/atm/ueagle-atm.mod := printf '%s\n'   ueagle-atm.o | awk '!x[$$0]++ { print("drivers/usb/atm/"$$0) }' > drivers/usb/atm/ueagle-atm.mod
