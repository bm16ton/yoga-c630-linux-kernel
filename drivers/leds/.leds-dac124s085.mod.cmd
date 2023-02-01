cmd_drivers/leds/leds-dac124s085.mod := printf '%s\n'   leds-dac124s085.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-dac124s085.mod
