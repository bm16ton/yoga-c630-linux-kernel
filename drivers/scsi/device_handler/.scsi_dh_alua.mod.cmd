cmd_drivers/scsi/device_handler/scsi_dh_alua.mod := printf '%s\n'   scsi_dh_alua.o | awk '!x[$$0]++ { print("drivers/scsi/device_handler/"$$0) }' > drivers/scsi/device_handler/scsi_dh_alua.mod
