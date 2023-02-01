cmd_drivers/mmc/host/sdhci.mod := printf '%s\n'   sdhci.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci.mod
