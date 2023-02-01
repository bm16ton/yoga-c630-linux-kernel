cmd_drivers/net/wireless/marvell/mwl8k.mod := printf '%s\n'   mwl8k.o | awk '!x[$$0]++ { print("drivers/net/wireless/marvell/"$$0) }' > drivers/net/wireless/marvell/mwl8k.mod
