cmd_drivers/leds/trigger/ledtrig-netdev.mod := printf '%s\n'   ledtrig-netdev.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-netdev.mod
