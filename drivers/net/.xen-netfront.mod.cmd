cmd_drivers/net/xen-netfront.mod := printf '%s\n'   xen-netfront.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/xen-netfront.mod
