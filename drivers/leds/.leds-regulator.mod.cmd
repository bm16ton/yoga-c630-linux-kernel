cmd_drivers/leds/leds-regulator.mod := printf '%s\n'   leds-regulator.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-regulator.mod
