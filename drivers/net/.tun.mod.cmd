cmd_drivers/net/tun.mod := printf '%s\n'   tun.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/tun.mod
