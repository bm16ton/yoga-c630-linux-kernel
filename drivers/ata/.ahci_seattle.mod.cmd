cmd_drivers/ata/ahci_seattle.mod := printf '%s\n'   ahci_seattle.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_seattle.mod
