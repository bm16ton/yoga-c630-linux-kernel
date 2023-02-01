cmd_drivers/leds/trigger/ledtrig-default-on.mod := printf '%s\n'   ledtrig-default-on.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-default-on.mod
