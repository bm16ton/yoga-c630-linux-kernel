cmd_drivers/bluetooth/btintel.mod := printf '%s\n'   btintel.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btintel.mod
