cmd_drivers/net/virtio_net.mod := printf '%s\n'   virtio_net.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/virtio_net.mod
