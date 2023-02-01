cmd_net/core/drop_monitor.mod := printf '%s\n'   drop_monitor.o | awk '!x[$$0]++ { print("net/core/"$$0) }' > net/core/drop_monitor.mod
