cmd_drivers/ata/pata_ninja32.mod := printf '%s\n'   pata_ninja32.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_ninja32.mod
