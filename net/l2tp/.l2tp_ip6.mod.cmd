cmd_net/l2tp/l2tp_ip6.mod := printf '%s\n'   l2tp_ip6.o | awk '!x[$$0]++ { print("net/l2tp/"$$0) }' > net/l2tp/l2tp_ip6.mod
