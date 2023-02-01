cmd_drivers/phy/rockchip/phy-rockchip-usb.mod := printf '%s\n'   phy-rockchip-usb.o | awk '!x[$$0]++ { print("drivers/phy/rockchip/"$$0) }' > drivers/phy/rockchip/phy-rockchip-usb.mod
