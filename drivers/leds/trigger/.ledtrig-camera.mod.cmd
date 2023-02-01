cmd_drivers/leds/trigger/ledtrig-camera.mod := printf '%s\n'   ledtrig-camera.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-camera.mod
