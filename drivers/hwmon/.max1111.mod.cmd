cmd_drivers/hwmon/max1111.mod := printf '%s\n'   max1111.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max1111.mod
