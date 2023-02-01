cmd_drivers/hid/hid-holtek-mouse.mod := printf '%s\n'   hid-holtek-mouse.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-holtek-mouse.mod
