cmd_net/netfilter/ipvs/ip_vs_sh.mod := printf '%s\n'   ip_vs_sh.o | awk '!x[$$0]++ { print("net/netfilter/ipvs/"$$0) }' > net/netfilter/ipvs/ip_vs_sh.mod
