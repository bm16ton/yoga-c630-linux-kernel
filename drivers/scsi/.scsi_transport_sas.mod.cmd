cmd_drivers/scsi/scsi_transport_sas.mod := printf '%s\n'   scsi_transport_sas.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/scsi_transport_sas.mod
