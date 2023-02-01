cmd_drivers/net/ppp/ppp_async.mod := printf '%s\n'   ppp_async.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/ppp_async.mod
