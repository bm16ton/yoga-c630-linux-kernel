cmd_drivers/leds/leds-gpio.mod := printf '%s\n'   leds-gpio.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-gpio.mod
