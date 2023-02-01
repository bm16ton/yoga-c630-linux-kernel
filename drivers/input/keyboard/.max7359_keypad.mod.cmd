cmd_drivers/input/keyboard/max7359_keypad.mod := printf '%s\n'   max7359_keypad.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/max7359_keypad.mod
