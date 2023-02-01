cmd_drivers/phy/rockchip/phy-rockchip-emmc.mod := printf '%s\n'   phy-rockchip-emmc.o | awk '!x[$$0]++ { print("drivers/phy/rockchip/"$$0) }' > drivers/phy/rockchip/phy-rockchip-emmc.mod
