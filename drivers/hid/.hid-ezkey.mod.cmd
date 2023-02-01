cmd_drivers/hid/hid-ezkey.mod := printf '%s\n'   hid-ezkey.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-ezkey.mod
