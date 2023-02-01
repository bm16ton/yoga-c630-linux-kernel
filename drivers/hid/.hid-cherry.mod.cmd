cmd_drivers/hid/hid-cherry.mod := printf '%s\n'   hid-cherry.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-cherry.mod
