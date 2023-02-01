cmd_net/6lowpan/nhc_dest.mod := printf '%s\n'   nhc_dest.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_dest.mod
