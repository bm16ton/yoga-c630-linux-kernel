cmd_drivers/ata/ahci_tegra.mod := printf '%s\n'   ahci_tegra.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/ahci_tegra.mod
