cmd_drivers/media/spi/gs1662.mod := printf '%s\n'   gs1662.o | awk '!x[$$0]++ { print("drivers/media/spi/"$$0) }' > drivers/media/spi/gs1662.mod
