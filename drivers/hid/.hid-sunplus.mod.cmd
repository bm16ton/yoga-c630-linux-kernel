cmd_drivers/hid/hid-sunplus.mod := printf '%s\n'   hid-sunplus.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-sunplus.mod
