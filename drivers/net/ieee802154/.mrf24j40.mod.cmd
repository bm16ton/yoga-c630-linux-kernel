cmd_drivers/net/ieee802154/mrf24j40.mod := printf '%s\n'   mrf24j40.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/mrf24j40.mod
