cmd_drivers/leds/leds-lm3532.mod := printf '%s\n'   leds-lm3532.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-lm3532.mod
