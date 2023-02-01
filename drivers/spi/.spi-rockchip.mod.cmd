cmd_drivers/spi/spi-rockchip.mod := printf '%s\n'   spi-rockchip.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-rockchip.mod
