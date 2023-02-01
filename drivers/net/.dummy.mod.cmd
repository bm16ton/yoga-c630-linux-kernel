cmd_drivers/net/dummy.mod := printf '%s\n'   dummy.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/dummy.mod
