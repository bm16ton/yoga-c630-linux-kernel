cmd_drivers/scsi/scsi_transport_srp.mod := printf '%s\n'   scsi_transport_srp.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/scsi_transport_srp.mod
