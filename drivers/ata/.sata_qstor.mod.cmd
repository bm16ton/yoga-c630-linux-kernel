cmd_drivers/ata/sata_qstor.mod := printf '%s\n'   sata_qstor.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_qstor.mod
