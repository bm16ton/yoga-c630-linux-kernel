cmd_drivers/hwmon/ina209.mod := printf '%s\n'   ina209.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ina209.mod
