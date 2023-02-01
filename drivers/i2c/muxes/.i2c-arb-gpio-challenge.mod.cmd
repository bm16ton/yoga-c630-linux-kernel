cmd_drivers/i2c/muxes/i2c-arb-gpio-challenge.mod := printf '%s\n'   i2c-arb-gpio-challenge.o | awk '!x[$$0]++ { print("drivers/i2c/muxes/"$$0) }' > drivers/i2c/muxes/i2c-arb-gpio-challenge.mod
