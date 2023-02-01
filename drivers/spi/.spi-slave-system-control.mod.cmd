cmd_drivers/spi/spi-slave-system-control.mod := printf '%s\n'   spi-slave-system-control.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-slave-system-control.mod
