cmd_drivers/net/netconsole.mod := printf '%s\n'   netconsole.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/netconsole.mod
