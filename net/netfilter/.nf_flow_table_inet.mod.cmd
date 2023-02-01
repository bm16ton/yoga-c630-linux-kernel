cmd_net/netfilter/nf_flow_table_inet.mod := printf '%s\n'   nf_flow_table_inet.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_flow_table_inet.mod
