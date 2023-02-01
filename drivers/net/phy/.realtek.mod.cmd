cmd_drivers/net/phy/realtek.mod := printf '%s\n'   realtek.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/realtek.mod
