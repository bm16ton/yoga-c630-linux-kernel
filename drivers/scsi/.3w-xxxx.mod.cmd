cmd_drivers/scsi/3w-xxxx.mod := printf '%s\n'   3w-xxxx.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/3w-xxxx.mod
