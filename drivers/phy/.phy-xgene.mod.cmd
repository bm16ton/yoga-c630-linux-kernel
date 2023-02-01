cmd_drivers/phy/phy-xgene.mod := printf '%s\n'   phy-xgene.o | awk '!x[$$0]++ { print("drivers/phy/"$$0) }' > drivers/phy/phy-xgene.mod
