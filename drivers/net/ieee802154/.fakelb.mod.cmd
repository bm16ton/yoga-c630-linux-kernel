cmd_drivers/net/ieee802154/fakelb.mod := printf '%s\n'   fakelb.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/fakelb.mod
