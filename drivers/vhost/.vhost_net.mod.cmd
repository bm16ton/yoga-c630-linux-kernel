cmd_drivers/vhost/vhost_net.mod := printf '%s\n'   net.o | awk '!x[$$0]++ { print("drivers/vhost/"$$0) }' > drivers/vhost/vhost_net.mod
