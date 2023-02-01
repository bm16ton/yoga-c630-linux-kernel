cmd_drivers/leds/leds-is31fl319x.mod := printf '%s\n'   leds-is31fl319x.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-is31fl319x.mod
