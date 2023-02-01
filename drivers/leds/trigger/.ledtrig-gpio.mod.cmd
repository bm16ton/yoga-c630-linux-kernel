cmd_drivers/leds/trigger/ledtrig-gpio.mod := printf '%s\n'   ledtrig-gpio.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-gpio.mod
