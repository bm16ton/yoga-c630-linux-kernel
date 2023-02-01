cmd_drivers/hwmon/ads7871.mod := printf '%s\n'   ads7871.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ads7871.mod
