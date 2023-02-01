cmd_drivers/spi/spi-bitbang.mod := printf '%s\n'   spi-bitbang.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-bitbang.mod
