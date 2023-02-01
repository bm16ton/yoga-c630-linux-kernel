cmd_net/qrtr/qrtr-tun.mod := printf '%s\n'   tun.o | awk '!x[$$0]++ { print("net/qrtr/"$$0) }' > net/qrtr/qrtr-tun.mod
