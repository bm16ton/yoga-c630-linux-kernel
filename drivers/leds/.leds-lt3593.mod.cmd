cmd_drivers/leds/leds-lt3593.mod := printf '%s\n'   leds-lt3593.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-lt3593.mod
