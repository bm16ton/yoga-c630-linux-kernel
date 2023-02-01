cmd_drivers/net/phy/vitesse.mod := printf '%s\n'   vitesse.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/vitesse.mod
