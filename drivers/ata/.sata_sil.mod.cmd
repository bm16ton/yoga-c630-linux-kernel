cmd_drivers/ata/sata_sil.mod := printf '%s\n'   sata_sil.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_sil.mod
