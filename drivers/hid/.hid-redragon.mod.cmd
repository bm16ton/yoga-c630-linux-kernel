cmd_drivers/hid/hid-redragon.mod := printf '%s\n'   hid-redragon.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-redragon.mod
