cmd_drivers/hid/uhid.mod := printf '%s\n'   uhid.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/uhid.mod
