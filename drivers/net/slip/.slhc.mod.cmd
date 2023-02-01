cmd_drivers/net/slip/slhc.mod := printf '%s\n'   slhc.o | awk '!x[$$0]++ { print("drivers/net/slip/"$$0) }' > drivers/net/slip/slhc.mod
