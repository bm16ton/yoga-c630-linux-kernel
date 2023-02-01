cmd_drivers/net/geneve.mod := printf '%s\n'   geneve.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/geneve.mod
