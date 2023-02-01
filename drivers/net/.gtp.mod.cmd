cmd_drivers/net/gtp.mod := printf '%s\n'   gtp.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/gtp.mod
