cmd_drivers/scsi/dmx3191d.mod := printf '%s\n'   dmx3191d.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/dmx3191d.mod
