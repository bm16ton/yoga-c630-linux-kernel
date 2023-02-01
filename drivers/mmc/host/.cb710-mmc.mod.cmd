cmd_drivers/mmc/host/cb710-mmc.mod := printf '%s\n'   cb710-mmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/cb710-mmc.mod
