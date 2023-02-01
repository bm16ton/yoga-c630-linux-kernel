cmd_drivers/hid/hid-icade.mod := printf '%s\n'   hid-icade.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-icade.mod
