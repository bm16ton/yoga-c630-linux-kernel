cmd_drivers/bluetooth/btrsi.mod := printf '%s\n'   btrsi.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btrsi.mod
