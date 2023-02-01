cmd_drivers/spi/spi-nxp-fspi.mod := printf '%s\n'   spi-nxp-fspi.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-nxp-fspi.mod
