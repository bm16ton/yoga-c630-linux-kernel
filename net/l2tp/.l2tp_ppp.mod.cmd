cmd_net/l2tp/l2tp_ppp.mod := printf '%s\n'   l2tp_ppp.o | awk '!x[$$0]++ { print("net/l2tp/"$$0) }' > net/l2tp/l2tp_ppp.mod
