cmd_drivers/scsi/3w-9xxx.mod := printf '%s\n'   3w-9xxx.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/3w-9xxx.mod
