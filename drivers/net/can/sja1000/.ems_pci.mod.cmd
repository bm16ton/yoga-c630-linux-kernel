cmd_drivers/net/can/sja1000/ems_pci.mod := printf '%s\n'   ems_pci.o | awk '!x[$$0]++ { print("drivers/net/can/sja1000/"$$0) }' > drivers/net/can/sja1000/ems_pci.mod
