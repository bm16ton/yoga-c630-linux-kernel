cmd_drivers/net/ifb.mod := printf '%s\n'   ifb.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/ifb.mod
