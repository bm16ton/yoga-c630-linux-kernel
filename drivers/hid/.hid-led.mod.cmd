cmd_drivers/hid/hid-led.mod := printf '%s\n'   hid-led.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-led.mod
