cmd_drivers/leds/trigger/ledtrig-audio.mod := printf '%s\n'   ledtrig-audio.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-audio.mod
