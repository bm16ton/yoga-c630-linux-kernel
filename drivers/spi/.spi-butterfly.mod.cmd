cmd_drivers/spi/spi-butterfly.mod := printf '%s\n'   spi-butterfly.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-butterfly.mod
