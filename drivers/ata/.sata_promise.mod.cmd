cmd_drivers/ata/sata_promise.mod := printf '%s\n'   sata_promise.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/sata_promise.mod
