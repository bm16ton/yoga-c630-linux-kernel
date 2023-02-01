cmd_net/dccp/dccp_ipv6.mod := printf '%s\n'   ipv6.o | awk '!x[$$0]++ { print("net/dccp/"$$0) }' > net/dccp/dccp_ipv6.mod
