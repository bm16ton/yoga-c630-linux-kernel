cmd_drivers/phy/rockchip/phy-rockchip-dp.mod := printf '%s\n'   phy-rockchip-dp.o | awk '!x[$$0]++ { print("drivers/phy/rockchip/"$$0) }' > drivers/phy/rockchip/phy-rockchip-dp.mod
