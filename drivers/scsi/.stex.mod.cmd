cmd_drivers/scsi/stex.mod := printf '%s\n'   stex.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/stex.mod
