cmd_drivers/leds/leds-is31fl32xx.mod := printf '%s\n'   leds-is31fl32xx.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-is31fl32xx.mod
