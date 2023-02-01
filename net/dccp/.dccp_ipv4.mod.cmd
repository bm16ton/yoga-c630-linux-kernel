cmd_net/dccp/dccp_ipv4.mod := printf '%s\n'   ipv4.o | awk '!x[$$0]++ { print("net/dccp/"$$0) }' > net/dccp/dccp_ipv4.mod
