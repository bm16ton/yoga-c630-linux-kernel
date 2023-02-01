cmd_drivers/net/ieee802154/ca8210.mod := printf '%s\n'   ca8210.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/ca8210.mod
