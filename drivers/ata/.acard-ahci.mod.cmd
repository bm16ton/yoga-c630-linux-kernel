cmd_drivers/ata/acard-ahci.mod := printf '%s\n'   acard-ahci.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/acard-ahci.mod
