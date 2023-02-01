cmd_drivers/net/hamradio/6pack.mod := printf '%s\n'   6pack.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/6pack.mod
