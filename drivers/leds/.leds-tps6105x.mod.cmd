cmd_drivers/leds/leds-tps6105x.mod := printf '%s\n'   leds-tps6105x.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-tps6105x.mod
