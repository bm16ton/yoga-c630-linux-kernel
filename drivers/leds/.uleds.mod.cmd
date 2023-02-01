cmd_drivers/leds/uleds.mod := printf '%s\n'   uleds.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/uleds.mod
