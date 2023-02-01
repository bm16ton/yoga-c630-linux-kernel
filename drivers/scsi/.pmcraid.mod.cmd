cmd_drivers/scsi/pmcraid.mod := printf '%s\n'   pmcraid.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/pmcraid.mod
