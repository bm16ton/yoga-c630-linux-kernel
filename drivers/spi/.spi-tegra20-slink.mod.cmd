cmd_drivers/spi/spi-tegra20-slink.mod := printf '%s\n'   spi-tegra20-slink.o | awk '!x[$$0]++ { print("drivers/spi/"$$0) }' > drivers/spi/spi-tegra20-slink.mod
