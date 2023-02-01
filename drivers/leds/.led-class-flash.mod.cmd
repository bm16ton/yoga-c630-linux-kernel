cmd_drivers/leds/led-class-flash.mod := printf '%s\n'   led-class-flash.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/led-class-flash.mod
