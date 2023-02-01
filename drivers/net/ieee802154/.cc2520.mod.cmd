cmd_drivers/net/ieee802154/cc2520.mod := printf '%s\n'   cc2520.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/cc2520.mod
