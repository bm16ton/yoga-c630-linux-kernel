cmd_drivers/mmc/host/sdhci-tegra.mod := printf '%s\n'   sdhci-tegra.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-tegra.mod
