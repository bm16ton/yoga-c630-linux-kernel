cmd_net/l2tp/l2tp_debugfs.mod := printf '%s\n'   l2tp_debugfs.o | awk '!x[$$0]++ { print("net/l2tp/"$$0) }' > net/l2tp/l2tp_debugfs.mod
