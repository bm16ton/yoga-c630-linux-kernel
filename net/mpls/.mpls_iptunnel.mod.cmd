cmd_net/mpls/mpls_iptunnel.mod := printf '%s\n'   mpls_iptunnel.o | awk '!x[$$0]++ { print("net/mpls/"$$0) }' > net/mpls/mpls_iptunnel.mod
