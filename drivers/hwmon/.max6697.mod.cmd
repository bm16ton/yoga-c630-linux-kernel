cmd_drivers/hwmon/max6697.mod := printf '%s\n'   max6697.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max6697.mod
