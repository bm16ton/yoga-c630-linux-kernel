cmd_drivers/leds/leds-blinkm.mod := printf '%s\n'   leds-blinkm.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-blinkm.mod
