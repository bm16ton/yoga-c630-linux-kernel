cmd_drivers/spi/spi-armada-3700.mod := printf '%s\n'   spi-armada-3700.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-armada-3700.mod
