cmd_net/nfc/nfc.mod := printf '%s\n'   core.o netlink.o af_nfc.o rawsock.o llcp_core.o llcp_commands.o llcp_sock.o | awk '!x[$$0]++ { print("net/nfc/"$$0) }' > net/nfc/nfc.mod
