cmd_drivers/mfd/tps6507x.mod := printf '%s\n'   tps6507x.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/tps6507x.mod
