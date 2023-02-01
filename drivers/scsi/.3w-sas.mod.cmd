cmd_drivers/scsi/3w-sas.mod := printf '%s\n'   3w-sas.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/3w-sas.mod
