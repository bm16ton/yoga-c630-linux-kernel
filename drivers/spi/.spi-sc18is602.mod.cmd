cmd_drivers/spi/spi-sc18is602.mod := printf '%s\n'   spi-sc18is602.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-sc18is602.mod
