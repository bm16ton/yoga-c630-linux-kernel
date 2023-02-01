cmd_drivers/net/ieee802154/adf7242.mod := printf '%s\n'   adf7242.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/adf7242.mod
