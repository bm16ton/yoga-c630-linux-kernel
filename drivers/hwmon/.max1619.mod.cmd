cmd_drivers/hwmon/max1619.mod := printf '%s\n'   max1619.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max1619.mod
