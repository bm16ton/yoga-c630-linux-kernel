cmd_drivers/input/keyboard/gpio_keys.mod := printf '%s\n'   gpio_keys.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/gpio_keys.mod
