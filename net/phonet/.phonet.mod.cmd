cmd_net/phonet/phonet.mod := printf '%s\n'   pn_dev.o pn_netlink.o socket.o datagram.o sysctl.o af_phonet.o | awk '!x[$$0]++ { print("net/phonet/"$$0) }' > net/phonet/phonet.mod
