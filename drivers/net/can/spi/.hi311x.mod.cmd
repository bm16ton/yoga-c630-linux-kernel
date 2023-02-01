cmd_drivers/net/can/spi/hi311x.mod := printf '%s\n'   hi311x.o | awk '!x[$$0]++ { print("drivers/net/can/spi/"$$0) }' > drivers/net/can/spi/hi311x.mod
