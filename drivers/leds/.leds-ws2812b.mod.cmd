cmd_drivers/leds/leds-ws2812b.mod := printf '%s\n'   leds-ws2812b.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-ws2812b.mod
