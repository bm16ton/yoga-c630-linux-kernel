cmd_drivers/hid/hid-alps.mod := printf '%s\n'   hid-alps.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-alps.mod
