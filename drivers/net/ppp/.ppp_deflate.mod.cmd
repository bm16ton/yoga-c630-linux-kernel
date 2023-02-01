cmd_drivers/net/ppp/ppp_deflate.mod := printf '%s\n'   ppp_deflate.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/ppp_deflate.mod
