cmd_drivers/mfd/axp20x.mod := printf '%s\n'   axp20x.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/axp20x.mod
