cmd_drivers/net/ppp/ppp_synctty.mod := printf '%s\n'   ppp_synctty.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/ppp_synctty.mod
