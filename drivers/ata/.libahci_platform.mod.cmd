cmd_drivers/ata/libahci_platform.mod := printf '%s\n'   libahci_platform.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/libahci_platform.mod
