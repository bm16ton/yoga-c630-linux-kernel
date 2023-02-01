cmd_drivers/bluetooth/btbcm.mod := printf '%s\n'   btbcm.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btbcm.mod
