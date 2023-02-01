cmd_drivers/hid/hid-saitek.mod := printf '%s\n'   hid-saitek.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-saitek.mod
