cmd_drivers/scsi/fcoe/fcoe.mod := printf '%s\n'   fcoe.o | awk '!x[$$0]++ { print("drivers/scsi/fcoe/"$$0) }' > drivers/scsi/fcoe/fcoe.mod
