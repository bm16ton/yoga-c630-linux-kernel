cmd_drivers/net/appletalk/ipddp.mod := printf '%s\n'   ipddp.o | awk '!x[$$0]++ { print("drivers/net/appletalk/"$$0) }' > drivers/net/appletalk/ipddp.mod
