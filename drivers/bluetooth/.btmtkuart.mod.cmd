cmd_drivers/bluetooth/btmtkuart.mod := printf '%s\n'   btmtkuart.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btmtkuart.mod
