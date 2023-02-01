cmd_net/6lowpan/nhc_fragment.mod := printf '%s\n'   nhc_fragment.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_fragment.mod
