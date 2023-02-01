cmd_drivers/input/keyboard/adc-keys.mod := printf '%s\n'   adc-keys.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/adc-keys.mod
