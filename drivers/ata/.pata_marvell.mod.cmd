cmd_drivers/ata/pata_marvell.mod := printf '%s\n'   pata_marvell.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_marvell.mod
