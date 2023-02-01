cmd_drivers/mfd/wl1273-core.mod := printf '%s\n'   wl1273-core.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/wl1273-core.mod
