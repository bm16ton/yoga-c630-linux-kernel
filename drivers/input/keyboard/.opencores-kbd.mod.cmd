cmd_drivers/input/keyboard/opencores-kbd.mod := printf '%s\n'   opencores-kbd.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/opencores-kbd.mod
