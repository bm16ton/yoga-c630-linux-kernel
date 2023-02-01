cmd_drivers/leds/trigger/ledtrig-backlight.mod := printf '%s\n'   ledtrig-backlight.o | awk '!x[$$0]++ { print("drivers/leds/trigger/"$$0) }' > drivers/leds/trigger/ledtrig-backlight.mod
