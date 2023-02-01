cmd_drivers/spi/spi-xlp.mod := printf '%s\n'   spi-xlp.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-xlp.mod
