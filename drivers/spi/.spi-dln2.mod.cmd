cmd_drivers/spi/spi-dln2.mod := printf '%s\n'   spi-dln2.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-dln2.mod
