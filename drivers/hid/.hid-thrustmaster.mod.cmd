cmd_drivers/hid/hid-thrustmaster.mod := printf '%s\n'   hid-thrustmaster.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-thrustmaster.mod
