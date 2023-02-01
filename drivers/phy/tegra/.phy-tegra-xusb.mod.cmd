cmd_drivers/phy/tegra/phy-tegra-xusb.mod := printf '%s\n'   xusb.o xusb-tegra124.o xusb-tegra210.o | awk '!x[$$0]++ { print("drivers/phy/tegra/"$$0) }' > drivers/phy/tegra/phy-tegra-xusb.mod
