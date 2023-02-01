cmd_drivers/mmc/host/via-sdmmc.mod := printf '%s\n'   via-sdmmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/via-sdmmc.mod
