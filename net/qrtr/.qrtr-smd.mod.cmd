cmd_net/qrtr/qrtr-smd.mod := printf '%s\n'   smd.o | awk '!x[$$0]++ { print("net/qrtr/"$$0) }' > net/qrtr/qrtr-smd.mod
