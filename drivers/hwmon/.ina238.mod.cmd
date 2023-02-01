cmd_drivers/hwmon/ina238.mod := printf '%s\n'   ina238.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ina238.mod
