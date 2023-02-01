cmd_net/sctp/sctp_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/sctp/"$$0) }' > net/sctp/sctp_diag.mod
