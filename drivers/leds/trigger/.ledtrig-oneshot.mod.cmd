cmd_drivers/leds/trigger/ledtrig-oneshot.mod := printf '%s\n'   ledtrig-oneshot.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-oneshot.mod
