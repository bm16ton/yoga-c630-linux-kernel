cmd_drivers/mmc/host/sdhci-of-arasan.mod := printf '%s\n'   sdhci-of-arasan.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-of-arasan.mod
