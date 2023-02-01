cmd_drivers/hid/hid-elo.mod := printf '%s\n'   hid-elo.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-elo.mod
