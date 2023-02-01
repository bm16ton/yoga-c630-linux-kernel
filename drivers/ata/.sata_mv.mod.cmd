cmd_drivers/ata/sata_mv.mod := printf '%s\n'   sata_mv.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_mv.mod
