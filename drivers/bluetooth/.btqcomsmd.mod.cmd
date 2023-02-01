cmd_drivers/bluetooth/btqcomsmd.mod := printf '%s\n'   btqcomsmd.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btqcomsmd.mod
