cmd_drivers/i2c/muxes/i2c-mux-gpio.mod := printf '%s\n'   i2c-mux-gpio.o | awk '!x[$$0]++ { print("drivers/i2c/muxes/"$$0) }' > drivers/i2c/muxes/i2c-mux-gpio.mod
