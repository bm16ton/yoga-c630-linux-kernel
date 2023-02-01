cmd_drivers/virtio/virtio_mmio.mod := printf '%s\n'   virtio_mmio.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_mmio.mod
