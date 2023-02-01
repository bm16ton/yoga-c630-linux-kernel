cmd_net/qrtr/qrtr.mod := printf '%s\n'   af_qrtr.o ns.o | awk '!x[$$0]++ { print("net/qrtr/"$$0) }' > net/qrtr/qrtr.mod
