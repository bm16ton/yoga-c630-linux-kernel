cmd_drivers/spi/spi-loopback-test.mod := printf '%s\n'   spi-loopback-test.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-loopback-test.mod
