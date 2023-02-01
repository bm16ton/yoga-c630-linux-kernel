cmd_drivers/leds/trigger/ledtrig-pattern.mod := printf '%s\n'   ledtrig-pattern.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-pattern.mod
