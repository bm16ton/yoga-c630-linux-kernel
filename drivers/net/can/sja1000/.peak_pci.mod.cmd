cmd_drivers/net/can/sja1000/peak_pci.mod := printf '%s\n'   peak_pci.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/peak_pci.mod
