cmd_drivers/scsi/advansys.mod := printf '%s\n'   advansys.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/advansys.mod
