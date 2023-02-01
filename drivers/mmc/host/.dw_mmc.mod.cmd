cmd_drivers/mmc/host/dw_mmc.mod := printf '%s\n'   dw_mmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/dw_mmc.mod
