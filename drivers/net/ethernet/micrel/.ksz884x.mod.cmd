cmd_drivers/net/ethernet/micrel/ksz884x.mod := printf '%s\n'   ksz884x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/micrel/"$$0) }' > drivers/net/ethernet/micrel/ksz884x.mod
