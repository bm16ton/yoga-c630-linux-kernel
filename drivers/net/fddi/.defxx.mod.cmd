cmd_drivers/net/fddi/defxx.mod := printf '%s\n'   defxx.o | awk '!x[$$0]++ { print("drivers/net/fddi/"$$0) }' > drivers/net/fddi/defxx.mod
