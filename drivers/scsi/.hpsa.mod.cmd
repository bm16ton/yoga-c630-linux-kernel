cmd_drivers/scsi/hpsa.mod := printf '%s\n'   hpsa.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/hpsa.mod
