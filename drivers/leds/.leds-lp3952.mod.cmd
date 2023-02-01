cmd_drivers/leds/leds-lp3952.mod := printf '%s\n'   leds-lp3952.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-lp3952.mod
