cmd_drivers/block/virtio_blk.mod := printf '%s\n'   virtio_blk.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/virtio_blk.mod
