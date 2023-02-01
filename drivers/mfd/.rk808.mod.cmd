cmd_drivers/mfd/rk808.mod := printf '%s\n'   rk808.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/rk808.mod
