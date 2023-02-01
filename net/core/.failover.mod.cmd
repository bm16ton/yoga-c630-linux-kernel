cmd_net/core/failover.mod := printf '%s\n'   failover.o | awk '!x[$$0]++ { print("net/core/"$$0) }' > net/core/failover.mod
