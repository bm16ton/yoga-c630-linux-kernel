cmd_drivers/hwmon/ina3221.mod := printf '%s\n'   ina3221.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ina3221.mod
