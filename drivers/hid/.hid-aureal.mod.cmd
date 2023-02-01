cmd_drivers/hid/hid-aureal.mod := printf '%s\n'   hid-aureal.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-aureal.mod
