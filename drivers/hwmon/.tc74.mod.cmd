cmd_drivers/hwmon/tc74.mod := printf '%s\n'   tc74.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tc74.mod
