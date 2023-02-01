cmd_net/qrtr/qrtr-mhi.mod := printf '%s\n'   mhi.o | awk '!x[$$0]++ { print("net/qrtr/"$$0) }' > net/qrtr/qrtr-mhi.mod
