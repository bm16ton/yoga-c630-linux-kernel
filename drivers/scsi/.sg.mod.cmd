cmd_drivers/scsi/sg.mod := printf '%s\n'   sg.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/sg.mod
