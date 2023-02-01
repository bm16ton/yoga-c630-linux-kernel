cmd_drivers/bluetooth/btmtksdio.mod := printf '%s\n'   btmtksdio.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btmtksdio.mod
