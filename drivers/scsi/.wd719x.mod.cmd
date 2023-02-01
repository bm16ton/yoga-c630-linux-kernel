cmd_drivers/scsi/wd719x.mod := printf '%s\n'   wd719x.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/wd719x.mod
