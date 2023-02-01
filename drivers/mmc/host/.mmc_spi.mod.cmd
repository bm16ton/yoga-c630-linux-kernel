cmd_drivers/mmc/host/mmc_spi.mod := printf '%s\n'   mmc_spi.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/mmc_spi.mod
