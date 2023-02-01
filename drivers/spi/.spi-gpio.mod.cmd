cmd_drivers/spi/spi-gpio.mod := printf '%s\n'   spi-gpio.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-gpio.mod
