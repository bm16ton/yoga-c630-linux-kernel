cmd_drivers/bluetooth/bcm203x.mod := printf '%s\n'   bcm203x.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/bcm203x.mod
