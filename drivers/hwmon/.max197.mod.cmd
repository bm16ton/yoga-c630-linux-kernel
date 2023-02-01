cmd_drivers/hwmon/max197.mod := printf '%s\n'   max197.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max197.mod
