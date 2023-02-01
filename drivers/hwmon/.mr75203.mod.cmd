cmd_drivers/hwmon/mr75203.mod := printf '%s\n'   mr75203.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/mr75203.mod
