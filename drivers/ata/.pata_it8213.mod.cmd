cmd_drivers/ata/pata_it8213.mod := printf '%s\n'   pata_it8213.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_it8213.mod
