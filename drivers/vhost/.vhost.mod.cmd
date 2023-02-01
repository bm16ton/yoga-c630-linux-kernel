cmd_drivers/vhost/vhost.mod := printf '%s\n'   vhost.o | awk '!x[$$0]++ { print("drivers/vhost/"$$0) }' > drivers/vhost/vhost.mod
