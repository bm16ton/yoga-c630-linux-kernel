cmd_drivers/scsi/raid_class.mod := printf '%s\n'   raid_class.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/raid_class.mod
