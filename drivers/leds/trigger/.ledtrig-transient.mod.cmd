cmd_drivers/leds/trigger/ledtrig-transient.mod := printf '%s\n'   ledtrig-transient.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-transient.mod
