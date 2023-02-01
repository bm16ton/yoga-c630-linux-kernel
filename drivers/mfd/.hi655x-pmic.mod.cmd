cmd_drivers/mfd/hi655x-pmic.mod := printf '%s\n'   hi655x-pmic.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/hi655x-pmic.mod
