cmd_drivers/mmc/host/tifm_sd.mod := printf '%s\n'   tifm_sd.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/tifm_sd.mod
