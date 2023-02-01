cmd_drivers/video/backlight/led_bl.mod := printf '%s\n'   led_bl.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/led_bl.mod
