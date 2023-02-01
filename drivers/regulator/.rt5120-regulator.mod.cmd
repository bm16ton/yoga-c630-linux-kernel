cmd_drivers/regulator/rt5120-regulator.mod := printf '%s\n'   rt5120-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/rt5120-regulator.mod
