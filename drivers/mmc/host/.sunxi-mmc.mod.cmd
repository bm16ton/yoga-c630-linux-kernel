cmd_drivers/mmc/host/sunxi-mmc.mod := printf '%s\n'   sunxi-mmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/sunxi-mmc.mod
