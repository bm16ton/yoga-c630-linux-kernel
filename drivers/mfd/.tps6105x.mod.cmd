cmd_drivers/mfd/tps6105x.mod := printf '%s\n'   tps6105x.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/tps6105x.mod
