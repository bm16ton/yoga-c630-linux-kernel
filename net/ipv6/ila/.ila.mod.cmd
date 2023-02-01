cmd_net/ipv6/ila/ila.mod := printf '%s\n'   ila_main.o ila_common.o ila_lwt.o ila_xlat.o | awk '!x[$$0]++ { print("net/ipv6/ila/"$$0) }' > net/ipv6/ila/ila.mod
