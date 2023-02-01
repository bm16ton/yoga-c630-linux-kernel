cmd_net/dccp/dccp_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/dccp/"$$0) }' > net/dccp/dccp_diag.mod
