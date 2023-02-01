cmd_drivers/ata/pata_atp867x.mod := printf '%s\n'   pata_atp867x.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_atp867x.mod
