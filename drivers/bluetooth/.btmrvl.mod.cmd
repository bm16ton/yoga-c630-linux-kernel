cmd_drivers/bluetooth/btmrvl.mod := printf '%s\n'   btmrvl_main.o btmrvl_debugfs.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btmrvl.mod
