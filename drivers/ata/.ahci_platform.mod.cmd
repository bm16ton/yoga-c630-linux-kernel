cmd_drivers/ata/ahci_platform.mod := printf '%s\n'   ahci_platform.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_platform.mod
