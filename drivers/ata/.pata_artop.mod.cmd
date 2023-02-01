cmd_drivers/ata/pata_artop.mod := printf '%s\n'   pata_artop.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_artop.mod
