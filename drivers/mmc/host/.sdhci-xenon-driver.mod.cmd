cmd_drivers/mmc/host/sdhci-xenon-driver.mod := printf '%s\n'   sdhci-xenon.o sdhci-xenon-phy.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-xenon-driver.mod
