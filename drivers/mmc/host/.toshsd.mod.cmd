cmd_drivers/mmc/host/toshsd.mod := printf '%s\n'   toshsd.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/toshsd.mod
