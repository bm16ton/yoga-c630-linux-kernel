cmd_drivers/ata/pdc_adma.mod := printf '%s\n'   pdc_adma.o | awk '!x[$$0]++ { print("drivers/ata/"$$0) }' > drivers/ata/pdc_adma.mod
