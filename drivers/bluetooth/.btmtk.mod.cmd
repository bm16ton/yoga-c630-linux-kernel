cmd_drivers/bluetooth/btmtk.mod := printf '%s\n'   btmtk.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btmtk.mod
