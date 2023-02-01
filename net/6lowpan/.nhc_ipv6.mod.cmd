cmd_net/6lowpan/nhc_ipv6.mod := printf '%s\n'   nhc_ipv6.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_ipv6.mod
