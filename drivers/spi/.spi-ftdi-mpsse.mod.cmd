cmd_drivers/spi/spi-ftdi-mpsse.mod := printf '%s\n'   spi-ftdi-mpsse.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-ftdi-mpsse.mod
