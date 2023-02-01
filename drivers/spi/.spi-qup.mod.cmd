cmd_drivers/spi/spi-qup.mod := printf '%s\n'   spi-qup.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-qup.mod
