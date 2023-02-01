cmd_drivers/mmc/host/sdhci-msm.mod := printf '%s\n'   sdhci-msm.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-msm.mod
