cmd_drivers/net/phy/cortina.mod := printf '%s\n'   cortina.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/cortina.mod
