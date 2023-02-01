cmd_drivers/phy/hisilicon/phy-hi6220-usb.mod := printf '%s\n'   phy-hi6220-usb.o | awk '!x[$$0]++ { print("drivers/phy/hisilicon/"$$0) }' > drivers/phy/hisilicon/phy-hi6220-usb.mod
