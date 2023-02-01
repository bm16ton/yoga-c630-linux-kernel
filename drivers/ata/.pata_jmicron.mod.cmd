cmd_drivers/ata/pata_jmicron.mod := printf '%s\n'   pata_jmicron.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pata_jmicron.mod
