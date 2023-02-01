cmd_drivers/net/ieee802154/at86rf230.mod := printf '%s\n'   at86rf230.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/at86rf230.mod
