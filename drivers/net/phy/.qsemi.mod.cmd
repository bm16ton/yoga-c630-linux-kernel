cmd_drivers/net/phy/qsemi.mod := printf '%s\n'   qsemi.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/qsemi.mod
