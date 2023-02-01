cmd_drivers/leds/leds-spi-byte.mod := printf '%s\n'   leds-spi-byte.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-spi-byte.mod
