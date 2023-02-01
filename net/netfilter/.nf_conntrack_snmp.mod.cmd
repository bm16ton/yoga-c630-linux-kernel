cmd_net/netfilter/nf_conntrack_snmp.mod := printf '%s\n'   nf_conntrack_snmp.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_conntrack_snmp.mod
