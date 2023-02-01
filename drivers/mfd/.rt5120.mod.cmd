cmd_drivers/mfd/rt5120.mod := printf '%s\n'   rt5120.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/rt5120.mod
