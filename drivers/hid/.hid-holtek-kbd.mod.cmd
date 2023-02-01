cmd_drivers/hid/hid-holtek-kbd.mod := printf '%s\n'   hid-holtek-kbd.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-holtek-kbd.mod
