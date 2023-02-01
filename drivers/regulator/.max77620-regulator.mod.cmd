cmd_drivers/regulator/max77620-regulator.mod := printf '%s\n'   max77620-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/max77620-regulator.mod
