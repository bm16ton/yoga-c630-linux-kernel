cmd_drivers/phy/allwinner/phy-sun4i-usb.mod := printf '%s\n'   phy-sun4i-usb.o | awk '!x[$$0]++ { print("drivers/phy/allwinner/"$$0) }' > drivers/phy/allwinner/phy-sun4i-usb.mod
