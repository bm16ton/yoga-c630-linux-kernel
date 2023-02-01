cmd_drivers/hwmon/max6650.mod := printf '%s\n'   max6650.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max6650.mod
