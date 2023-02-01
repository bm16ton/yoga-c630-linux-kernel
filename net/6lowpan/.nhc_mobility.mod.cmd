cmd_net/6lowpan/nhc_mobility.mod := printf '%s\n'   nhc_mobility.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_mobility.mod
