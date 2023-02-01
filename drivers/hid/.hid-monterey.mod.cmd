cmd_drivers/hid/hid-monterey.mod := printf '%s\n'   hid-monterey.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-monterey.mod
