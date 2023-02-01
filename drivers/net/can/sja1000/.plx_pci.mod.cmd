cmd_drivers/net/can/sja1000/plx_pci.mod := printf '%s\n'   plx_pci.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/plx_pci.mod
