cmd_drivers/regulator/hi655x-regulator.mod := printf '%s\n'   hi655x-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/hi655x-regulator.mod
