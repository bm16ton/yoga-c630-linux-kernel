cmd_drivers/hid/hid-mf.mod := printf '%s\n'   hid-mf.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-mf.mod
