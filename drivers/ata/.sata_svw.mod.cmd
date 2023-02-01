cmd_drivers/ata/sata_svw.mod := printf '%s\n'   sata_svw.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_svw.mod
