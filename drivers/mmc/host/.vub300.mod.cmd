cmd_drivers/mmc/host/vub300.mod := printf '%s\n'   vub300.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/vub300.mod
