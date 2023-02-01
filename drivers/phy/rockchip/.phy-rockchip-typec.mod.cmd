cmd_drivers/phy/rockchip/phy-rockchip-typec.mod := printf '%s\n'   phy-rockchip-typec.o | awk '!x[$$0]++ { print("drivers/phy/rockchip/"$$0) }' > drivers/phy/rockchip/phy-rockchip-typec.mod
