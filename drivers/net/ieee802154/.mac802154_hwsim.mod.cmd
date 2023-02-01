cmd_drivers/net/ieee802154/mac802154_hwsim.mod := printf '%s\n'   mac802154_hwsim.o | awk '!x[$$0]++ { print("drivers/net/ieee802154/"$$0) }' > drivers/net/ieee802154/mac802154_hwsim.mod
