cmd_drivers/hwmon/max6621.mod := printf '%s\n'   max6621.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max6621.mod
