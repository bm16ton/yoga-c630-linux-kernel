cmd_net/l2tp/l2tp_ip.mod := printf '%s\n'   l2tp_ip.o | awk '!x[$$0]++ { print("net/l2tp/"$$0) }' > net/l2tp/l2tp_ip.mod
