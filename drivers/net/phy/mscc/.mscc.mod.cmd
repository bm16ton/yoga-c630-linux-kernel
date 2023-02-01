cmd_drivers/net/phy/mscc/mscc.mod := printf '%s\n'   mscc_main.o mscc_serdes.o mscc_macsec.o | awk '!x[$$0]++ { print("drivers/net/phy/mscc/"$$0) }' > drivers/net/phy/mscc/mscc.mod
