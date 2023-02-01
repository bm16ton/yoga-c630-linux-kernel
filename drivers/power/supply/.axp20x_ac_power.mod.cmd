cmd_drivers/power/supply/axp20x_ac_power.mod := printf '%s\n'   axp20x_ac_power.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/axp20x_ac_power.mod
