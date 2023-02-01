cmd_drivers/vhost/vhost_scsi.mod := printf '%s\n'   scsi.o | awk '!x[$$0]++ { print("drivers/vhost/"$$0) }' > drivers/vhost/vhost_scsi.mod
