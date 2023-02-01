cmd_drivers/scsi/libiscsi_tcp.mod := printf '%s\n'   libiscsi_tcp.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/libiscsi_tcp.mod
