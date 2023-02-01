cmd_drivers/net/net_failover.mod := printf '%s\n'   net_failover.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/net_failover.mod
