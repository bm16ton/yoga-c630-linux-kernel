cmd_drivers/video/backlight/lcd.mod := printf '%s\n'   lcd.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/lcd.mod
