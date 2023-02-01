cmd_drivers/bluetooth/btsdio.mod := printf '%s\n'   btsdio.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btsdio.mod
