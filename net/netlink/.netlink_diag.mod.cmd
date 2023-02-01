cmd_net/netlink/netlink_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/netlink/"$$0) }' > net/netlink/netlink_diag.mod
