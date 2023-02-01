cmd_drivers/ata/libahci.mod := printf '%s\n'   libahci.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/libahci.mod
