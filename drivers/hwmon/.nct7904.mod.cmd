cmd_drivers/hwmon/nct7904.mod := printf '%s\n'   nct7904.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nct7904.mod
