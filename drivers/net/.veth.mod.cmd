cmd_drivers/net/veth.mod := printf '%s\n'   veth.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/veth.mod
