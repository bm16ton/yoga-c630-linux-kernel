cmd_drivers/scsi/iscsi_tcp.mod := printf '%s\n'   iscsi_tcp.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/iscsi_tcp.mod
