cmd_net/netfilter/nf_synproxy_core.mod := printf '%s\n'   nf_synproxy_core.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_synproxy_core.mod
