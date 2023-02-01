cmd_drivers/scsi/atp870u.mod := printf '%s\n'   atp870u.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/atp870u.mod
