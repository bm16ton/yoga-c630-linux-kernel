cmd_drivers/hid/hid-steam.mod := printf '%s\n'   hid-steam.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-steam.mod
