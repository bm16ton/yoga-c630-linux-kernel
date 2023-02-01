cmd_drivers/scsi/mvumi.mod := printf '%s\n'   mvumi.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/mvumi.mod
