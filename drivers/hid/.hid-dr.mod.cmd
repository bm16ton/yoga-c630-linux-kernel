cmd_drivers/hid/hid-dr.mod := printf '%s\n'   hid-dr.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-dr.mod
