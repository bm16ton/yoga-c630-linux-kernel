cmd_drivers/leds/leds-lp3944.mod := printf '%s\n'   leds-lp3944.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-lp3944.mod
