cmd_drivers/net/can/sja1000/kvaser_pci.mod := printf '%s\n'   kvaser_pci.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/kvaser_pci.mod
