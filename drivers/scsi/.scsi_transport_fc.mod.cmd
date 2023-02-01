cmd_drivers/scsi/scsi_transport_fc.mod := printf '%s\n'   scsi_transport_fc.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/scsi_transport_fc.mod
