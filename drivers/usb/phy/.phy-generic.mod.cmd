cmd_drivers/usb/phy/phy-generic.mod := printf '%s\n'   phy-generic.o | awk '!x[$$0]++ { print("drivers/usb/phy/"$$0) }' > drivers/usb/phy/phy-generic.mod
