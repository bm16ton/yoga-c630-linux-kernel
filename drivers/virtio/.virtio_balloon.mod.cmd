cmd_drivers/virtio/virtio_balloon.mod := printf '%s\n'   virtio_balloon.o | awk '!x[$$0]++ { print("drivers/virtio/"$$0) }' > drivers/virtio/virtio_balloon.mod
