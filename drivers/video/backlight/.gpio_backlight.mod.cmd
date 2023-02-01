cmd_drivers/video/backlight/gpio_backlight.mod := printf '%s\n'   gpio_backlight.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/gpio_backlight.mod
