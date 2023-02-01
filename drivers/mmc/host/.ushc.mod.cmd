cmd_drivers/mmc/host/ushc.mod := printf '%s\n'   ushc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/ushc.mod
