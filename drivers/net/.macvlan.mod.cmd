cmd_drivers/net/macvlan.mod := printf '%s\n'   macvlan.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/macvlan.mod
