cmd_drivers/ata/pata_it821x.mod := printf '%s\n'   pata_it821x.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_it821x.mod
