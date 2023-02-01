cmd_drivers/spi/spi-meson-spifc.mod := printf '%s\n'   spi-meson-spifc.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-meson-spifc.mod
