cmd_drivers/hid/hid-belkin.mod := printf '%s\n'   hid-belkin.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-belkin.mod
