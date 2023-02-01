cmd_drivers/net/hamradio/mkiss.mod := printf '%s\n'   mkiss.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/mkiss.mod
