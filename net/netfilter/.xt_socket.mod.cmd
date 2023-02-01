cmd_net/netfilter/xt_socket.mod := printf '%s\n'   xt_socket.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_socket.mod
