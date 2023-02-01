cmd_drivers/input/keyboard/cros_ec_keyb.mod := printf '%s\n'   cros_ec_keyb.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/cros_ec_keyb.mod
