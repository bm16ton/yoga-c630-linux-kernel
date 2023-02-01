cmd_drivers/spi/spi-thunderx.mod := printf '%s\n'   spi-cavium.o spi-cavium-thunderx.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-thunderx.mod
