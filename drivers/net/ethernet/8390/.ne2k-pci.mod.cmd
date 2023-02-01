cmd_drivers/net/ethernet/8390/ne2k-pci.mod := printf '%s\n'   ne2k-pci.o | awk '!x[$$0]++ { print("drivers/net/ethernet/8390/"$$0) }' > drivers/net/ethernet/8390/ne2k-pci.mod
