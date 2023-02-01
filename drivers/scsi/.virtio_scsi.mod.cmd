cmd_drivers/scsi/virtio_scsi.mod := printf '%s\n'   virtio_scsi.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/virtio_scsi.mod
