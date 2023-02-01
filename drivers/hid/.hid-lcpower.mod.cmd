cmd_drivers/hid/hid-lcpower.mod := printf '%s\n'   hid-lcpower.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-lcpower.mod
