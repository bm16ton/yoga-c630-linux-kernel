cmd_drivers/leds/rgb/leds-pwm-multicolor.mod := printf '%s\n'   leds-pwm-multicolor.o | awk '!x[$$0]++ { print("drivers/leds/rgb/"$$0) }' > drivers/leds/rgb/leds-pwm-multicolor.mod
