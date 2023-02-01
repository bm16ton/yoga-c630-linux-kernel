cmd_drivers/leds/trigger/ledtrig-timer.mod := printf '%s\n'   ledtrig-timer.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-timer.mod
