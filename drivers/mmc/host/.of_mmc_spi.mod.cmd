cmd_drivers/mmc/host/of_mmc_spi.mod := printf '%s\n'   of_mmc_spi.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/of_mmc_spi.mod
