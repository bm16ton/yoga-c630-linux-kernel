cmd_drivers/hwmon/max31730.mod := printf '%s\n'   max31730.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max31730.mod
