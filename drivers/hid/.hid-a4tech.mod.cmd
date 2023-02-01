cmd_drivers/hid/hid-a4tech.mod := printf '%s\n'   hid-a4tech.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-a4tech.mod
