cmd_drivers/leds/leds-lm3530.mod := printf '%s\n'   leds-lm3530.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-lm3530.mod
