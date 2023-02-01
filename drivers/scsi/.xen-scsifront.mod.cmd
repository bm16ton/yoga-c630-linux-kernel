cmd_drivers/scsi/xen-scsifront.mod := printf '%s\n'   xen-scsifront.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/xen-scsifront.mod
