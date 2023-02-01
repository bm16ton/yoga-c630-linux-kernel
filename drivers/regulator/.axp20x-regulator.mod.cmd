cmd_drivers/regulator/axp20x-regulator.mod := printf '%s\n'   axp20x-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/axp20x-regulator.mod
