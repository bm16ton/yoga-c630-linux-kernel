cmd_drivers/net/ppp/pppoe.mod := printf '%s\n'   pppoe.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/pppoe.mod
