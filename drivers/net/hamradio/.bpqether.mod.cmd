cmd_drivers/net/hamradio/bpqether.mod := printf '%s\n'   bpqether.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/bpqether.mod
