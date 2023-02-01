cmd_drivers/hid/hid-pl.mod := printf '%s\n'   hid-pl.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-pl.mod
