cmd_drivers/scsi/ses.mod := printf '%s\n'   ses.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/ses.mod
