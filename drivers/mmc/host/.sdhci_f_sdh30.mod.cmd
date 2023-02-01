cmd_drivers/mmc/host/sdhci_f_sdh30.mod := printf '%s\n'   sdhci_f_sdh30.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci_f_sdh30.mod
