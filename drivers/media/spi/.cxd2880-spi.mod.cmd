cmd_drivers/media/spi/cxd2880-spi.mod := printf '%s\n'   cxd2880-spi.o | awk '!x[$$0]++ { print("drivers/media/spi/"$$0) }' > drivers/media/spi/cxd2880-spi.mod
