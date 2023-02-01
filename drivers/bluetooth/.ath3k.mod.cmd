cmd_drivers/bluetooth/ath3k.mod := printf '%s\n'   ath3k.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/ath3k.mod
