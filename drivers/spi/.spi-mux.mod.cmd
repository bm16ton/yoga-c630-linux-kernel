cmd_drivers/spi/spi-mux.mod := printf '%s\n'   spi-mux.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-mux.mod
