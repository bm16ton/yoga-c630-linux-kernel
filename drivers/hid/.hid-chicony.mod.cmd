cmd_drivers/hid/hid-chicony.mod := printf '%s\n'   hid-chicony.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-chicony.mod
