cmd_drivers/bluetooth/btqca.mod := printf '%s\n'   btqca.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btqca.mod
