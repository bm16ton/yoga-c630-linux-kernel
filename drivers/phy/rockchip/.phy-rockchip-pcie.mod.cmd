cmd_drivers/phy/rockchip/phy-rockchip-pcie.mod := printf '%s\n'   phy-rockchip-pcie.o | awk '!x[$$0]++ { print("drivers/phy/rockchip/"$$0) }' > drivers/phy/rockchip/phy-rockchip-pcie.mod
