cmd_drivers/ata/sata_nv.mod := printf '%s\n'   sata_nv.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_nv.mod
