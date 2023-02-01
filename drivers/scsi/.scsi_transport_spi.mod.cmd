cmd_drivers/scsi/scsi_transport_spi.mod := printf '%s\n'   scsi_transport_spi.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/scsi_transport_spi.mod
