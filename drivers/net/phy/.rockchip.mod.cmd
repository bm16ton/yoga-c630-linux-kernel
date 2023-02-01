cmd_drivers/net/phy/rockchip.mod := printf '%s\n'   rockchip.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/rockchip.mod
