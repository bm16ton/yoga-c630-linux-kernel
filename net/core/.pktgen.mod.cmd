cmd_net/core/pktgen.mod := printf '%s\n'   pktgen.o | awk '!x[$$0]++ { print("net/core/"$$0) }' > net/core/pktgen.mod
