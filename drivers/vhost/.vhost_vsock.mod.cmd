cmd_drivers/vhost/vhost_vsock.mod := printf '%s\n'   vsock.o | awk '!x[$$0]++ { print("drivers/vhost/"$$0) }' > drivers/vhost/vhost_vsock.mod
