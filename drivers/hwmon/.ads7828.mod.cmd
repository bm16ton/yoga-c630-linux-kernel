cmd_drivers/hwmon/ads7828.mod := printf '%s\n'   ads7828.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ads7828.mod
