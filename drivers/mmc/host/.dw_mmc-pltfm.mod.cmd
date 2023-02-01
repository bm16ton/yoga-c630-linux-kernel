cmd_drivers/mmc/host/dw_mmc-pltfm.mod := printf '%s\n'   dw_mmc-pltfm.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/dw_mmc-pltfm.mod
