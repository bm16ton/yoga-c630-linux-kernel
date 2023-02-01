cmd_drivers/hid/hid-corsair.mod := printf '%s\n'   hid-corsair.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-corsair.mod
