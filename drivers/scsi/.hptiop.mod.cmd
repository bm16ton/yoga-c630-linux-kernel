cmd_drivers/scsi/hptiop.mod := printf '%s\n'   hptiop.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/hptiop.mod
