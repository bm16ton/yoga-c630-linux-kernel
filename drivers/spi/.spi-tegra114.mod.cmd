cmd_drivers/spi/spi-tegra114.mod := printf '%s\n'   spi-tegra114.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-tegra114.mod
