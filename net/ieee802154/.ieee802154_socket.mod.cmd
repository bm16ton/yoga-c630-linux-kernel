cmd_net/ieee802154/ieee802154_socket.mod := printf '%s\n'   socket.o | awk '!x[$$0]++ { print("net/ieee802154/"$$0) }' > net/ieee802154/ieee802154_socket.mod
