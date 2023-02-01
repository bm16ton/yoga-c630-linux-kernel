cmd_drivers/ata/pata_cmd64x.mod := printf '%s\n'   pata_cmd64x.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_cmd64x.mod
