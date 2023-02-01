cmd_drivers/hwmon/max6620.mod := printf '%s\n'   max6620.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max6620.mod
