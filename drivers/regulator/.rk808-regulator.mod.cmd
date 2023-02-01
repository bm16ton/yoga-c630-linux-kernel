cmd_drivers/regulator/rk808-regulator.mod := printf '%s\n'   rk808-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/rk808-regulator.mod
