cmd_drivers/leds/trigger/ledtrig-heartbeat.mod := printf '%s\n'   ledtrig-heartbeat.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-heartbeat.mod
