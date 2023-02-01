cmd_drivers/regulator/tps6105x-regulator.mod := printf '%s\n'   tps6105x-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/tps6105x-regulator.mod
