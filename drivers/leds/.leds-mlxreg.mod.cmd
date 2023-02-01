cmd_drivers/leds/leds-mlxreg.mod := printf '%s\n'   leds-mlxreg.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-mlxreg.mod
