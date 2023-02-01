cmd_drivers/mmc/host/sdhci-pltfm.mod := printf '%s\n'   sdhci-pltfm.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-pltfm.mod
