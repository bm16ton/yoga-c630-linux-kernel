cmd_drivers/ata/ahci_ceva.mod := printf '%s\n'   ahci_ceva.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_ceva.mod
