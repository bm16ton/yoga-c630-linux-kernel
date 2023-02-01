cmd_drivers/net/ieee802154/atusb.mod := printf '%s\n'   atusb.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/atusb.mod
