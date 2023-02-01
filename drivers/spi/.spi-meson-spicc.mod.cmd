cmd_drivers/spi/spi-meson-spicc.mod := printf '%s\n'   spi-meson-spicc.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-meson-spicc.mod
