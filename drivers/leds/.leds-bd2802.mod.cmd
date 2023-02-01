cmd_drivers/leds/leds-bd2802.mod := printf '%s\n'   leds-bd2802.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-bd2802.mod
