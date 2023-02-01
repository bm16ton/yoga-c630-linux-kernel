cmd_drivers/input/keyboard/adp5588-keys.mod := printf '%s\n'   adp5588-keys.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/adp5588-keys.mod
