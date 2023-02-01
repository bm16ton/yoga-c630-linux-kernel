cmd_drivers/net/tap.mod := printf '%s\n'   tap.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/tap.mod
