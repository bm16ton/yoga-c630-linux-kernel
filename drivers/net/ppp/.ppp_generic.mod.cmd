cmd_drivers/net/ppp/ppp_generic.mod := printf '%s\n'   ppp_generic.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/ppp_generic.mod
