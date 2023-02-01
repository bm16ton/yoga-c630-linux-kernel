cmd_drivers/spi/spidev.mod := printf '%s\n'   spidev.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spidev.mod
