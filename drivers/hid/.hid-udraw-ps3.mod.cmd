cmd_drivers/hid/hid-udraw-ps3.mod := printf '%s\n'   hid-udraw-ps3.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-udraw-ps3.mod
