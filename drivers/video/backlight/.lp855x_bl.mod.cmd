cmd_drivers/video/backlight/lp855x_bl.mod := printf '%s\n'   lp855x_bl.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/lp855x_bl.mod
