cmd_drivers/scsi/ch.mod := printf '%s\n'   ch.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/ch.mod
