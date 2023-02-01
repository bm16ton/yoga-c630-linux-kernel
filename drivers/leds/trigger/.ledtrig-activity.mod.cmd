cmd_drivers/leds/trigger/ledtrig-activity.mod := printf '%s\n'   ledtrig-activity.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-activity.mod
