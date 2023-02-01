cmd_drivers/spi/spi-lm70llp.mod := printf '%s\n'   spi-lm70llp.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-lm70llp.mod
