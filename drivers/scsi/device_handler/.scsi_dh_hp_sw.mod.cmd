cmd_drivers/scsi/device_handler/scsi_dh_hp_sw.mod := printf '%s\n'   scsi_dh_hp_sw.o | awk '!x[$$0]++ { print("drivers/scsi/device_handler/"$$0) }' > drivers/scsi/device_handler/scsi_dh_hp_sw.mod
