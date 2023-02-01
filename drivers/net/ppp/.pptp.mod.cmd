cmd_drivers/net/ppp/pptp.mod := printf '%s\n'   pptp.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/pptp.mod
