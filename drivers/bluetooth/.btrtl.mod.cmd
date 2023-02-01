cmd_drivers/bluetooth/btrtl.mod := printf '%s\n'   btrtl.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btrtl.mod
