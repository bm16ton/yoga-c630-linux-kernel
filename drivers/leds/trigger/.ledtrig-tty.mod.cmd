cmd_drivers/leds/trigger/ledtrig-tty.mod := printf '%s\n'   ledtrig-tty.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-tty.mod
