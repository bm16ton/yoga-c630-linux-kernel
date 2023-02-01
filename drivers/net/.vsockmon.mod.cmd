cmd_drivers/net/vsockmon.mod := printf '%s\n'   vsockmon.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/vsockmon.mod
