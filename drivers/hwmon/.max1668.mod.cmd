cmd_drivers/hwmon/max1668.mod := printf '%s\n'   max1668.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max1668.mod
