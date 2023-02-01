cmd_net/netfilter/nf_conntrack_h323.mod := printf '%s\n'   nf_conntrack_h323_main.o nf_conntrack_h323_asn1.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_conntrack_h323.mod
