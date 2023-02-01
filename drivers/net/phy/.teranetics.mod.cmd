cmd_drivers/net/phy/teranetics.mod := printf '%s\n'   teranetics.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/teranetics.mod
