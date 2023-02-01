cmd_drivers/hid/hid-primax.mod := printf '%s\n'   hid-primax.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-primax.mod
