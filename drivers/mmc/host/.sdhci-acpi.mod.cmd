cmd_drivers/mmc/host/sdhci-acpi.mod := printf '%s\n'   sdhci-acpi.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sdhci-acpi.mod
