cmd_drivers/mfd/axp20x-rsb.mod := printf '%s\n'   axp20x-rsb.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/axp20x-rsb.mod
