cmd_drivers/hid/hid-ortek.mod := printf '%s\n'   hid-ortek.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-ortek.mod
