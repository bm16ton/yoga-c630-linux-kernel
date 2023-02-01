cmd_drivers/video/backlight/platform_lcd.mod := printf '%s\n'   platform_lcd.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/platform_lcd.mod
