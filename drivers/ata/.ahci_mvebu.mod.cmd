cmd_drivers/ata/ahci_mvebu.mod := printf '%s\n'   ahci_mvebu.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_mvebu.mod
