cmd_drivers/net/ppp/pppox.mod := printf '%s\n'   pppox.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/pppox.mod
