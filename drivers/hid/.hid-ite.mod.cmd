cmd_drivers/hid/hid-ite.mod := printf '%s\n'   hid-ite.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-ite.mod
