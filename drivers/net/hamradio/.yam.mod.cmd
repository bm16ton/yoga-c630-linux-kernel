cmd_drivers/net/hamradio/yam.mod := printf '%s\n'   yam.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/yam.mod
