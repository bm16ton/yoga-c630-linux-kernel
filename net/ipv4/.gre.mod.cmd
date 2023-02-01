cmd_net/ipv4/gre.mod := printf '%s\n'   gre_demux.o | awk '!x[$$0]++ { print("net/ipv4/"$$0) }' > net/ipv4/gre.mod
