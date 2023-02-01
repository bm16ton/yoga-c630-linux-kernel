cmd_drivers/leds/leds-pwm.mod := printf '%s\n'   leds-pwm.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-pwm.mod
