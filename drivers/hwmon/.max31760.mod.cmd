cmd_drivers/hwmon/max31760.mod := printf '%s\n'   max31760.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max31760.mod
