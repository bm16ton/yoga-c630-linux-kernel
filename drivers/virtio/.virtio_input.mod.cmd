cmd_drivers/virtio/virtio_input.mod := printf '%s\n'   virtio_input.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_input.mod
