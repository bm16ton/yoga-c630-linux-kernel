cmd_drivers/hwmon/max6639.mod := printf '%s\n'   max6639.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max6639.mod
