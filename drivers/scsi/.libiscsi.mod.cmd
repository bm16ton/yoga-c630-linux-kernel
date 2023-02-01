cmd_drivers/scsi/libiscsi.mod := printf '%s\n'   libiscsi.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/libiscsi.mod
