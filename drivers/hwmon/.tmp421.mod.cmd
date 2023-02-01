cmd_drivers/hwmon/tmp421.mod := printf '%s\n'   tmp421.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp421.mod
