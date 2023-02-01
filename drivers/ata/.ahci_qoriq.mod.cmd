cmd_drivers/ata/ahci_qoriq.mod := printf '%s\n'   ahci_qoriq.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_qoriq.mod
