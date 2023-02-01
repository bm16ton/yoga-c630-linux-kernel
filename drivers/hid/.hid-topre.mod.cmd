cmd_drivers/hid/hid-topre.mod := printf '%s\n'   hid-topre.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-topre.mod
