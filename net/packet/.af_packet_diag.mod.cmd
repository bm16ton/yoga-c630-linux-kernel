cmd_net/packet/af_packet_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/packet/"$$0) }' > net/packet/af_packet_diag.mod
