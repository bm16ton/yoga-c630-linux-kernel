cmd_net/6lowpan/nhc_routing.mod := printf '%s\n'   nhc_routing.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_routing.mod
