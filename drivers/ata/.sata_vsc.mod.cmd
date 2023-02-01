cmd_drivers/ata/sata_vsc.mod := printf '%s\n'   sata_vsc.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_vsc.mod
