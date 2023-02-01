cmd_drivers/net/eql.mod := printf '%s\n'   eql.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/eql.mod
