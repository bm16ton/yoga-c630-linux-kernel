cmd_drivers/ata/ahci_xgene.mod := printf '%s\n'   ahci_xgene.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_xgene.mod
