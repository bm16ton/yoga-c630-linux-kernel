cmd_drivers/ata/sata_sil24.mod := printf '%s\n'   sata_sil24.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_sil24.mod
