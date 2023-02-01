cmd_drivers/input/keyboard/lm8323.mod := printf '%s\n'   lm8323.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/lm8323.mod
