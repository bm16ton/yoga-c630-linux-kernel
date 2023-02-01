cmd_drivers/bluetooth/bpa10x.mod := printf '%s\n'   bpa10x.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/bpa10x.mod
