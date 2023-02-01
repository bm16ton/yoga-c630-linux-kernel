cmd_drivers/net/ieee802154/mcr20a.mod := printf '%s\n'   mcr20a.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/mcr20a.mod
