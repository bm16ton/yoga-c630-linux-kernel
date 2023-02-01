cmd_drivers/hid/hid-zydacron.mod := printf '%s\n'   hid-zydacron.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-zydacron.mod
