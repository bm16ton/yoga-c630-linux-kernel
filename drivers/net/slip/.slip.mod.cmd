cmd_drivers/net/slip/slip.mod := printf '%s\n'   slip.o | awk '!x[$$0]++ { print("drivers/net/slip/"$$0) }' > drivers/net/slip/slip.mod
