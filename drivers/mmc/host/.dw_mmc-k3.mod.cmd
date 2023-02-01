cmd_drivers/mmc/host/dw_mmc-k3.mod := printf '%s\n'   dw_mmc-k3.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/dw_mmc-k3.mod
